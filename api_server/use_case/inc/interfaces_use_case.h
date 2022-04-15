#ifndef CALMGRAM_API_SERVER_USE_CASE_INTERFACES_H
#define CALMGRAM_API_SERVER_USE_CASE_INTERFACES_H

#include "entities.h"

namespace calmgram::api_server::use_case {

namespace entities = ::calmgram::api_server::entities;

class IGetUser {
 public:
  virtual ~IGetUser(){};
  virtual entities::User GetUser(int id);
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
  virtual entities::Chat CreateChat(int id);
};

class IGetMsgs {
 public:
  virtual ~IGetMsgs() {}
  virtual std::vector<entities::Message> GetMsgs(int chat_id, time_t from_time);
};

class ISendMsg {
 public:
  virtual ~ISendMsg() {}
  virtual entities::Chat SendMsg(entities::Message const& msg, int chat_id);
};

class IAnalysisText {
 public:
  virtual ~IAnalysisText() {}
  virtual bool AnalysisText(std::string const& msg);
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_INTERFACES_H