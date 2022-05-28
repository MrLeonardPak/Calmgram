#ifndef API_CLIENT_INTERFACES_USER_UC_H
#define API_CLIENT_INTERFACES_USER_UC_H

#include "entities.h"

#include <string>
#include <vector>

namespace calmgram::api_client::use_case {

class IUserUC {
 public:
  virtual ~IUserUC() = default;

  virtual void Auth(std::string const& login, std::string const& password) = 0;
  virtual std::vector<entities::EmptyChat> GetChats() const = 0;
  virtual std::vector<entities::Message> OpenChat(int chat_id) = 0;
  virtual void CreateChat(
      std::vector<std::string> target_logins) const = 0;
  virtual void SendMessage(std::string const& str, int chat_id) const = 0;
  virtual void ReportAboutMark(std::string const& msg,
                               bool is_marked) const = 0;
  virtual void UpdateChats() = 0;
  virtual void Logout() = 0;
};
}  // namespace calmgram::api_client::use_case

#endif  // API_CLIENT_INTERFACES_USER_UC_H
