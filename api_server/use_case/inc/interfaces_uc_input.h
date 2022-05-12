#ifndef CALMGRAM_API_SERVER_USE_CASE_INTERFACES_INPUT_H
#define CALMGRAM_API_SERVER_USE_CASE_INTERFACES_INPUT_H

#include "entities.h"

#include <vector>

namespace calmgram::api_server::use_case {

class IUserAuthUC {
 public:
  virtual ~IUserAuthUC() = default;
  virtual std::vector<int> Execute(int user_id) = 0;
};

class IUpdateChatUC {
 public:
  virtual ~IUpdateChatUC() = default;
  virtual std::vector<entities::Message> Execute(int user_id,
                                                 int chat_id,
                                                 time_t from_time) = 0;
};

class ISendMsgUC {
 public:
  virtual ~ISendMsgUC() = default;
  virtual void Execute(int user_id,
                       int chat_id,
                       entities::Content const& content) = 0;
};

class IAddChatUC {
 public:
  virtual ~IAddChatUC() = default;
  virtual int Execute(std::vector<int> users) = 0;
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_INTERFACES_INPUT_H