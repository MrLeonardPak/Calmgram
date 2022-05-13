#include "postgre_sql.h"

namespace calmgram::api_server::libs::database {

PostgreSQL::PostgreSQL() {}

void PostgreSQL::CheckUser(int id) const {}

entities::User PostgreSQL::CreateUser(int id) const {}

int PostgreSQL::CreateChat() const {}

std::vector<entities::Message> PostgreSQL::GetMsgs(int chat_id,
                                                   time_t from_time) const {}

entities::User PostgreSQL::GetUser(int id) const {}

void PostgreSQL::SendMsg(entities::Message const& msg, int chat_id) const {}

void PostgreSQL::SetChat(std::vector<int> const& users, int chat_id) const {}

}  // namespace calmgram::api_server::libs::database