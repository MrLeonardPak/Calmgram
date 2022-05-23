#include "postgre_sql.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace calmgram::api_server::libs::database {

PostgreSQL::PostgreSQL(std::string const connection,
                       std::string const& init_file)
    : connect_(std::make_unique<pqxx::connection>(connection)) {
  std::cout << "Opened database successfully: " << connect_->dbname()
            << std::endl;

  auto file_stream = std::ifstream(init_file);
  if (!file_stream.is_open()) {
    throw std::runtime_error("Can't generate controller. None .sql file");
  }

  auto file_buffer = std::stringstream();
  file_buffer << file_stream.rdbuf();
  file_stream.close();

  auto tx = pqxx::work(*connect_);
  tx.exec(file_buffer.str());
  tx.commit();
}

pqxx::result PostgreSQL::Query(std::string query) const {
  auto tx = pqxx::work(*connect_);
  pqxx::result res = tx.exec(query);
  tx.commit();
  return res;
}

bool PostgreSQL::CheckUserExist(int user_id) const {
  auto ss = std::stringstream();
  ss << "SELECT id FROM users WHERE id=" << user_id;
  pqxx::result res = Query(ss.str());

  return !res.empty();
}

bool PostgreSQL::CheckUserAccessToChat(int user_id, int chat_id) const {
  auto ss = std::stringstream();
  ss << "SELECT chat_id FROM users_chats WHERE user_id=" << user_id;
  pqxx::result res = Query(ss.str());

  bool check = false;
  for (auto&& row : res) {
    if (row["chat_id"].as<int>() == chat_id) {
      check = true;
      break;
    }
  }

  return check;
}

entities::User PostgreSQL::CreateUser(int id) const {
  auto ss = std::stringstream();
  ss << "INSERT INTO users (login) VALUES (" << id << ") RETURNING id";
  pqxx::result res = Query(ss.str());
  return {res.at(0)["id"].as<int>(), {}};
}

int PostgreSQL::CreateChat() const {
  auto ss = std::stringstream();
  ss << "INSERT INTO chats DEFAULT VALUES RETURNING id";
  pqxx::result res = Query(ss.str());
  return res.at(0)["id"].as<int>();
}

std::vector<entities::Message> PostgreSQL::GetMsgs(int chat_id,
                                                   time_t from_time) const {
  auto ss = std::stringstream();
  ss << "SELECT * FROM messages WHERE created>"
     << "'" << std::put_time(std::gmtime(&from_time), "%F %T")
     << "' AND  chat_id=" << chat_id;
  pqxx::result res = Query(ss.str());

  auto msgs = std::vector<entities::Message>();
  auto msg = entities::Message();
  for (auto&& row : res) {
    msg.owner_id = row["owner_id"].as<int>();
    msg.content.text = row["text"].as<std::string>();
    msg.is_marked = row["is_marked"].as<bool>();

    auto ss_tmp = std::istringstream(row["created"].as<std::string>());
    std::tm tm = {};
    ss_tmp >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    msg.created = timegm(&tm);

    msgs.push_back(msg);
  }

  return msgs;
}

entities::User PostgreSQL::GetUser(int id) const {
  auto ss = std::stringstream();
  auto res = pqxx::result();

  ss << "SELECT id FROM users WHERE login="
     << "'" << id << "'";
  res = Query(ss.str());

  if (res.empty()) {
    throw std::logic_error("No user");
  }

  ss.str("");
  int user_id = res.at(0)["id"].as<int>();
  ss << "SELECT chat_id FROM users_chats WHERE user_id=" << user_id;
  res = Query(ss.str());

  auto chat_ids = std::vector<int>();
  for (auto&& row : res) {
    chat_ids.push_back(row["chat_id"].as<int>());
  }

  return {user_id, chat_ids};
}

void PostgreSQL::SendMsg(entities::Message const& msg, int chat_id) const {
  auto ss = std::stringstream();

  ss << "INSERT INTO messages (chat_id,owner_id,text,is_marked,created) VALUES "
        "("
     << chat_id << "," << msg.owner_id << ","
     << "'" << msg.content.text << "'"
     << ","
     << "'" << msg.is_marked << "'"
     << ","
     << "'" << std::put_time(std::gmtime(&msg.created), "%Y-%m-%d %H:%M:%S")
     << "'"
     << ")";
  Query(ss.str());
}

void PostgreSQL::SetChat(std::vector<int> const& users, int chat_id) const {
  auto ss = std::stringstream();
  for (auto&& user_id : users) {
    ss.str("");
    ss << "INSERT INTO users_chats VALUES (" << user_id << "," << chat_id
       << ")";
    Query(ss.str());
  }
}

}  // namespace calmgram::api_server::libs::database
