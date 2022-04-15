#ifndef CALMGRAM_API_SERVER_USE_CASE_INTERFACES_H
#define CALMGRAM_API_SERVER_USE_CASE_INTERFACES_H

#include "entities.h"

namespace calmgram::api_server::use_case {

namespace entities = ::calmgram::api_server::entities;

class IGetUser {
 public:
  virtual ~IGetUser() = default;
  virtual entities::User GetUser(int id) = 0;
};

class ICreateUser {
 public:
  virtual ~ICreateUser() = default;
  virtual int CreateUser() = 0;
};

class ISetChat {
 public:
  virtual ~ISetChat() = default;
  virtual void SetChat(std::vector<int> users, int chat_id) = 0;
};

class ICreateChat {
 public:
  virtual ~ICreateChat() = default;
  virtual entities::Chat CreateChat(int id) = 0;
};

class IGetMsgs {
 public:
  virtual ~IGetMsgs() = default;
  virtual std::vector<entities::Message> GetMsgs(int chat_id,
                                                 time_t from_time) = 0;
};

class ISendMsg {
 public:
  virtual ~ISendMsg() = default;
  virtual entities::Chat SendMsg(entities::Message const& msg, int chat_id) = 0;
};

class IAnalysisText {
 public:
  virtual ~IAnalysisText() = default;
  virtual bool AnalysisText(std::string const& msg) = 0;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_INTERFACES_H