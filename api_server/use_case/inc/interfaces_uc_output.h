#ifndef CALMGRAM_API_SERVER_USE_CASE_INTERFACES_OUTPUT_H
#define CALMGRAM_API_SERVER_USE_CASE_INTERFACES_OUTPUT_H

#include "entities.h"

namespace calmgram::api_server::use_case {

class IGetUser {
 public:
  virtual ~IGetUser() = default;
  virtual entities::User GetUser(int id) const = 0;
};

class ICheckUserExist {
 public:
  virtual ~ICheckUserExist() = default;
  virtual bool CheckUserExist(int id) const = 0;
};

class ICheckUserAccessToChat {
 public:
  virtual ~ICheckUserAccessToChat() = default;
  virtual bool CheckUserAccessToChat(int user_id, int chat_id) const = 0;
};

class ICreateUser {
 public:
  virtual ~ICreateUser() = default;
  virtual entities::User CreateUser(int id) const = 0;
};

class ISetChat {
 public:
  virtual ~ISetChat() = default;
  virtual void SetChat(std::vector<int> const& users, int chat_id) const = 0;
};

class ICreateChat {
 public:
  virtual ~ICreateChat() = default;
  virtual int CreateChat() const = 0;
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
  virtual bool AnalysisText(std::string const& msg) const = 0;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_INTERFACES_OUTPUT_H