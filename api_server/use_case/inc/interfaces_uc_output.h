#ifndef CALMGRAM_API_SERVER_USE_CASE_INTERFACES_OUTPUT_H
#define CALMGRAM_API_SERVER_USE_CASE_INTERFACES_OUTPUT_H

#include "entities.h"

namespace calmgram::api_server::use_case {

class ICreateSession {
 public:
  virtual ~ICreateSession() = default;
  virtual std::string CreateSession(std::string_view user_login) = 0;
};

class IGetSessionLogin {
 public:
  virtual ~IGetSessionLogin() = default;
  virtual std::string GetSessionLogin(std::string_view token) const = 0;
};

class ICheckUser {
 public:
  virtual ~ICheckUser() = default;
  virtual bool CheckUser(std::string_view login,
                         std::string_view password) const = 0;
  virtual bool CheckUser(std::string_view login) const = 0;
};

class ICheckUserAccessToChat {
 public:
  virtual ~ICheckUserAccessToChat() = default;
  virtual bool CheckUserAccessToChat(std::string_view user_login,
                                     int chat_id) const = 0;
};

class ICreateUser {
 public:
  virtual ~ICreateUser() = default;
  virtual bool CreateUser(std::string_view login,
                          std::string_view password) const = 0;
};

class ICreateChat {
 public:
  virtual ~ICreateChat() = default;
  virtual int CreateChat(std::vector<std::string_view> const& users) const = 0;
};

class IGetChatList {
 public:
  virtual ~IGetChatList() = default;
  virtual std::vector<int> GetChatList(std::string_view user_login) const = 0;
};

class IGetMsgs {
 public:
  virtual ~IGetMsgs() = default;
  virtual std::vector<entities::Message> GetMsgs(int chat_id,
                                                 time_t from_time) const = 0;
};

class ISendMsg {
 public:
  virtual ~ISendMsg() = default;
  virtual void SendMsg(entities::Message const& msg, int chat_id) const = 0;
};

class IAnalysisText {
 public:
  virtual ~IAnalysisText() = default;
  virtual bool AnalysisText(std::string_view msg) const = 0;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_INTERFACES_OUTPUT_H