#ifndef CALMGRAM_API_SERVER_USE_CASE_INTERFACES_H
#define CALMGRAM_API_SERVER_USE_CASE_INTERFACES_H

#include "entity.h"

namespace calmgram::api_server::use_case {

namespace entity = ::calmgram::api_server::entity;

class IGetUser {
 public:
  virtual ~IGetUser(){};
  virtual entity::User GetUser(int id);
};

class ICreateUser {
 public:
  virtual ~ICreateUser() {}
  virtual int CreateUser();
};

class ISetChat {
 public:
  virtual ~ISetChat() {}
  virtual void SetChat(std::vector<int> users, int chat_id);
};

class ICreateChat {
 public:
  virtual ~ICreateChat() {}
  virtual entity::Chat CreateChat(int id);
};

class IGetMsgs {
 public:
  virtual ~IGetMsgs() {}
  virtual std::vector<entity::Message> GetMsgs(int chat_id, time_t from_time);
};

class ISendMsg {
 public:
  virtual ~ISendMsg() {}
  virtual entity::Chat SendMsg(entity::Message const& msg, int chat_id);
};

class IAnalysisText {
 public:
  virtual ~IAnalysisText() {}
  virtual bool AnalysisText(std::string const& msg);
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_INTERFACES_H