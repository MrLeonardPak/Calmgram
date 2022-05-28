#ifndef CALMGRAM_API_SERVER_LIBS_DATABASE_POSTGRE_SQL_H
#define CALMGRAM_API_SERVER_LIBS_DATABASE_POSTGRE_SQL_H

#include "interfaces_uc_output.h"

#include <pqxx/pqxx>

#include <sys/sysinfo.h>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace calmgram::api_server::libs::database {

class PostgreSQL : public use_case::ICheckUser,
                   public use_case::ICheckUserAccessToChat,
                   public use_case::ICreateChat,
                   public use_case::ICreateUser,
                   public use_case::IGetChatList,
                   public use_case::IGetUserListFromChat,
                   public use_case::IGetMsgs,
                   public use_case::ISendMsg {
 public:
  PostgreSQL(std::string_view connection,
             std::string_view init_file,
             size_t pool = get_nprocs());

  PostgreSQL(PostgreSQL const&) = delete;
  PostgreSQL(PostgreSQL&&) = delete;
  PostgreSQL& operator=(PostgreSQL const&) = delete;
  PostgreSQL& operator=(PostgreSQL&&) = delete;

  ~PostgreSQL() = default;

  bool CheckUser(std::string_view login,
                 std::string_view password) const override;

  bool CheckUser(std::string_view login) const override;

  bool CheckUserAccessToChat(std::string_view user_login,
                             int chat_id) const override;

  bool CreateUser(std::string_view login,
                  std::string_view password) const override;

  int CreateChat(std::vector<std::string_view> const& users) const override;

  std::vector<int> GetChatList(std::string_view user_login) const override;

  std::vector<std::string> GetUserListFromChat(int chat_id) const override;

  std::vector<entities::Message> GetMsgs(int chat_id,
                                         time_t from_time) const override;

  void SendMsg(entities::Message const& msg, int chat_id) const override;

 private:
  size_t const pool_ = 1;
  std::mutex mutable mutex_;
  std::condition_variable mutable condition_;
  std::queue<std::unique_ptr<pqxx::connection>> mutable connection_pool_;

  pqxx::result Query(std::string_view query) const;

  void CreatePool(std::string_view connection);
  std::unique_ptr<pqxx::connection> Connection() const;
  void FreeConnection(std::unique_ptr<pqxx::connection>&& conn) const;
};

}  // namespace calmgram::api_server::libs::database

#endif  // CALMGRAM_API_SERVER_LIBS_DATABASE_POSTGRE_SQL_H
