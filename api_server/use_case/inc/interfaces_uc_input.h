#ifndef CALMGRAM_API_SERVER_USE_CASE_INTERFACES_INPUT_H
#define CALMGRAM_API_SERVER_USE_CASE_INTERFACES_INPUT_H

#include "entities.h"

#include <vector>

namespace calmgram::api_server::use_case {

class IUserAuthUC {
 public:
  virtual ~IUserAuthUC() = default;
  virtual std::string Execute(std::string_view login,
                              std::string_view password) = 0;
};

class IUserLogoutUC {
 public:
  virtual ~IUserLogoutUC() = default;
  virtual void Execute(std::string_view token) = 0;
};

class IUpdateChatUC {
 public:
  virtual ~IUpdateChatUC() = default;
  virtual std::vector<entities::Message> Execute(std::string_view token,
                                                 int chat_id,
                                                 time_t from_time) = 0;
};

class ISendMsgUC {
 public:
  virtual ~ISendMsgUC() = default;
  virtual void Execute(std::string_view token,
                       int chat_id,
                       entities::Content const& content) = 0;
};

class IAddChatUC {
 public:
  virtual ~IAddChatUC() = default;
  virtual int Execute(std::string_view token,
                      std::vector<std::string_view> const& user_logins) = 0;
};

class IGetChatListUC {
 public:
  virtual ~IGetChatListUC() = default;
  virtual std::vector<entities::Chat> Execute(std::string_view token) = 0;
};

class IAddToDatasetUC {
 public:
  virtual ~IAddToDatasetUC() = default;
  virtual void Execute(std::string_view token,
                       std::string_view data,
                       bool label) = 0;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_INTERFACES_INPUT_H