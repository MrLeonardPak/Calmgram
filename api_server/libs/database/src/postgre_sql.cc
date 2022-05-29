#include "postgre_sql.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace calmgram::api_server::libs::database {

PostgreSQL::PostgreSQL(std::string_view connection,
                       std::string_view init_file,
                       size_t pool)
    : pool_(pool) {
  CreatePool(connection);
  std::cout << "Opened database successfully! Pool = " << pool << std::endl;
  auto file_stream = std::ifstream(init_file.data());
  if (!file_stream.is_open()) {
    throw std::runtime_error("Can't generate controller. None .sql file");
  }

  auto file_buffer = std::ostringstream();
  file_buffer << file_stream.rdbuf();
  file_stream.close();

  Query(file_buffer.view());
}

void PostgreSQL::CreatePool(std::string_view connection) {
  auto locker = std::scoped_lock<std::mutex>(mutex_);

  for (size_t i = 0; i < pool_; ++i) {
    connection_pool_.emplace(
        std::make_unique<pqxx::connection>(connection.data()));
  }
}

std::unique_ptr<pqxx::connection> PostgreSQL::Connection() const {
  auto locker = std::unique_lock<std::mutex>(mutex_);

  condition_.wait(locker, [&connection_pool_ = connection_pool_]() {
    return !connection_pool_.empty();
  });

  auto conn = std::move(connection_pool_.front());
  connection_pool_.pop();

  return conn;
}
void PostgreSQL::FreeConnection(
    std::unique_ptr<pqxx::connection>&& conn) const {
  auto locker = std::unique_lock<std::mutex>(mutex_);
  connection_pool_.push(std::move(conn));
  locker.unlock();
  condition_.notify_one();
}

pqxx::result PostgreSQL::Query(std::string_view query) const {
  auto conn = Connection();

  auto tx = pqxx::work(*conn);
  pqxx::result res = tx.exec(query);
  tx.commit();

  FreeConnection(std::move(conn));
  return res;
}

bool PostgreSQL::CheckUser(std::string_view login,
                           std::string_view password) const {
  auto ss = std::ostringstream();
  ss << "SELECT ";
  ss << "(login='" << login << "' AND pswhash=crypt('" << password
     << "',pswhash))";
  ss << " AS match FROM users WHERE login='" << login << "'";
  pqxx::result res = Query(ss.view());

  return (res.empty() ? false : res.at(0)["match"].as<bool>());
}

bool PostgreSQL::CheckUser(std::string_view login) const {
  auto ss = std::ostringstream();
  ss << "SELECT login FROM users WHERE login='" << login << "'";
  pqxx::result res = Query(ss.view());

  return !res.empty();
}

bool PostgreSQL::CheckUserAccessToChat(std::string_view user_login,
                                       int chat_id) const {
  auto ss = std::ostringstream();
  ss << "SELECT chat_id FROM users_chats ";
  ss << "WHERE user_login='" << user_login << "'";
  pqxx::result res = Query(ss.view());

  bool check = false;
  for (auto&& row : res) {
    if (row["chat_id"].as<int>() == chat_id) {
      check = true;
      break;
    }
  }

  return check;
}

bool PostgreSQL::CreateUser(std::string_view login,
                            std::string_view password) const {
  auto ss = std::ostringstream();
  ss << "INSERT INTO users VALUES ";
  ss << "('" << login << "', crypt('" << password << "',gen_salt('md5')))";

  bool res = true;
  try {
    Query(ss.view());
  } catch (pqxx::unique_violation const& e) {
    std::cout << e.what() << std::endl;
    res = false;
  }

  return res;
}

int PostgreSQL::CreateChat(std::vector<std::string_view> const& users) const {
  auto ss = std::ostringstream();
  ss << "INSERT INTO chats DEFAULT VALUES RETURNING id";
  pqxx::result res = Query(ss.view());
  auto chat_id = res.at(0)["id"].as<int>();

  ss.str("");
  for (auto&& login : users) {
    ss.str("");
    ss << "INSERT INTO users_chats VALUES ";
    ss << "('" << login << "'," << chat_id << ")";
    Query(ss.view());
  }

  return chat_id;
}

std::vector<entities::Message> PostgreSQL::GetMsgs(int chat_id,
                                                   time_t from_time) const {
  auto ss = std::ostringstream();
  ss << "SELECT * FROM messages WHERE";
  ss << " created>"
     << "'" << std::put_time(std::gmtime(&from_time), "%F %T") << "'";
  ss << " AND  chat_id=" << chat_id;
  pqxx::result res = Query(ss.view());

  auto msgs = std::vector<entities::Message>();
  auto msg = entities::Message();
  for (auto&& row : res) {
    msg.owner_login = row["owner_login"].as<std::string>();
    msg.content.text = row["text"].as<std::string>();
    msg.is_marked = row["is_marked"].as<bool>();

    auto ss_tmp = std::istringstream(row["created"].as<std::string>());
    auto tm = std::tm();
    ss_tmp >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    msg.created = timegm(&tm);

    msgs.push_back(msg);
  }

  return msgs;
}

std::vector<int> PostgreSQL::GetChatList(std::string_view user_login) const {
  auto ss = std::ostringstream();

  ss << "SELECT chat_id FROM users_chats WHERE";
  ss << " user_login='" << user_login << "'";
  pqxx::result res = Query(ss.view());

  auto chat_ids = std::vector<int>();
  for (auto&& row : res) {
    chat_ids.push_back(row["chat_id"].as<int>());
  }

  return chat_ids;
}

std::vector<std::string> PostgreSQL::GetUserListFromChat(int chat_id) const {
  auto ss = std::ostringstream();

  ss << "SELECT user_login FROM users_chats WHERE";
  ss << " chat_id=" << chat_id;
  pqxx::result res = Query(ss.view());

  auto user_logins = std::vector<std::string>();
  for (auto&& row : res) {
    user_logins.push_back(row["user_login"].as<std::string>());
  }

  return user_logins;
}

void PostgreSQL::SendMsg(entities::Message const& msg, int chat_id) const {
  auto ss = std::stringstream();

  ss << "INSERT INTO messages (chat_id,owner_login,text,is_marked,created) ";
  ss << "VALUES (" << chat_id << ",'" << msg.owner_login << "',"
     << "'" << msg.content.text << "'"
     << ","
     << "'" << msg.is_marked << "'"
     << ","
     << "'" << std::put_time(std::gmtime(&msg.created), "%Y-%m-%d %H:%M:%S")
     << "'"
     << ")";
  Query(ss.str());
}

}  // namespace calmgram::api_server::libs::database
