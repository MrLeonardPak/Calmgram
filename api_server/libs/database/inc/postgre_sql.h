#ifndef CALMGRAM_API_SERVER_LIBS_DATABASE_POSTGRE_SQL_H
#define CALMGRAM_API_SERVER_LIBS_DATABASE_POSTGRE_SQL_H

#include <pqxx/pqxx>
#include "interfaces_uc_output.h"

namespace calmgram::api_server::libs::database {

class PostgreSQL : public use_case::ICheckUserAccessToChat,
                   public use_case::ICheckUserExist,
                   public use_case::ICreateChat,
                   public use_case::ICreateUser,
                   public use_case::IGetMsgs,
                   public use_case::IGetUser,
                   public use_case::ISendMsg,
                   public use_case::ISetChat {
 public:
  PostgreSQL(std::string const connection, std::string const& init_file);

  PostgreSQL(PostgreSQL const&) = delete;
  PostgreSQL(PostgreSQL&&) = delete;
  PostgreSQL& operator=(PostgreSQL const&) = delete;
  PostgreSQL& operator=(PostgreSQL&&) = delete;

  ~PostgreSQL() = default;

  pqxx::result Query(std::string query) const;

  bool CheckUserExist(int user_id) const override;

  bool CheckUserAccessToChat(int user_id, int chat_id) const override;

  entities::User CreateUser(int id) const override;

  int CreateChat() const override;

  std::vector<entities::Message> GetMsgs(int chat_id,
                                         time_t from_time) const override;

  entities::User GetUser(int id) const override;

  void SendMsg(entities::Message const& msg, int chat_id) const override;

  void SetChat(std::vector<int> const& users, int chat_id) const override;

 private:
  std::unique_ptr<pqxx::connection> connect_;
};

}  // namespace calmgram::api_server::libs::database

#endif  // CALMGRAM_API_SERVER_LIBS_DATABASE_POSTGRE_SQL_H
