#ifndef CALMGRAM_API_SERVER_LIBS_DATABASE_POSTGRE_SQL_H
#define CALMGRAM_API_SERVER_LIBS_DATABASE_POSTGRE_SQL_H

#include <pqxx/pqxx>
#include "interfaces_uc_output.h"

namespace calmgram::api_server::libs::database {

class PostgreSQL : public use_case::ICheckUser,
                   public use_case::ICheckUserAccessToChat,
                   public use_case::ICreateChat,
                   public use_case::ICreateUser,
                   public use_case::IGetChatList,
                   public use_case::IGetMsgs,
                   public use_case::ISendMsg {
 public:
  PostgreSQL(std::string const connection, std::string const& init_file);

  PostgreSQL(PostgreSQL const&) = delete;
  PostgreSQL(PostgreSQL&&) = delete;
  PostgreSQL& operator=(PostgreSQL const&) = delete;
  PostgreSQL& operator=(PostgreSQL&&) = delete;

  ~PostgreSQL() = default;

  pqxx::result Query(std::string_view query) const;

  bool CheckUser(std::string_view login,
                 std::string_view password) const override;

  bool CheckUser(std::string_view login) const override;

  bool CheckUserAccessToChat(std::string_view user_login,
                             int chat_id) const override;

  bool CreateUser(std::string_view login,
                  std::string_view password) const override;

  int CreateChat(std::vector<std::string_view> const& users) const override;

  std::vector<int> GetChatList(std::string_view user_login) const override;

  std::vector<entities::Message> GetMsgs(int chat_id,
                                         time_t from_time) const override;

  void SendMsg(entities::Message const& msg, int chat_id) const override;

 private:
  std::unique_ptr<pqxx::connection> connect_;
};

}  // namespace calmgram::api_server::libs::database

#endif  // CALMGRAM_API_SERVER_LIBS_DATABASE_POSTGRE_SQL_H
