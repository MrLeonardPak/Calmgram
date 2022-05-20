#include "postgre_sql.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace calmgram::api_server::libs::database {

PostgreSQL::PostgreSQL(std::string const connection,
                       std::string const& init_file)
    : connect_("connection") {
  if (connect_.is_open()) {
    std::cout << "Opened database successfully: " << connect_.dbname()
              << std::endl;
  } else {
    throw std::runtime_error("Can't open database");
  }

  auto file_stream = std::ifstream(init_file);
  if (!file_stream.is_open()) {
    throw std::runtime_error("Can't generate controller. None .sql file");
  }

  std::stringstream file_buffer;
  file_buffer << file_stream.rdbuf();
  file_stream.close();

  auto tx = pqxx::work(connect_);
  tx.exec(file_buffer.str());
  tx.commit();
}

PostgreSQL::~PostgreSQL() {
  connect_.close();
}

void PostgreSQL::CheckUser(int id) const {}

entities::User PostgreSQL::CreateUser(int id) const {}

int PostgreSQL::CreateChat() const {}

std::vector<entities::Message> PostgreSQL::GetMsgs(int chat_id,
                                                   time_t from_time) const {}

entities::User PostgreSQL::GetUser(int id) const {}

void PostgreSQL::SendMsg(entities::Message const& msg, int chat_id) const {}

void PostgreSQL::SetChat(std::vector<int> const& users, int chat_id) const {}

}  // namespace calmgram::api_server::libs::database