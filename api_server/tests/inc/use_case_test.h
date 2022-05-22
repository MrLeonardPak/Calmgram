#ifndef CALMGRAM_API_SERVER_USE_CASE_TEST_H
#define CALMGRAM_API_SERVER_USE_CASE_TEST_H

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "add_chat_uc.h"
#include "send_msg_uc.h"
#include "update_chat_uc.h"
#include "user_auth_uc.h"

namespace calmgram::api_server::tests {

class MockIGetUser : public use_case::IGetUser {
 public:
  MOCK_METHOD(entities::User, GetUser, (int id), (const, override));
};

class MockICheckUserExist : public use_case::ICheckUserExist {
 public:
  MOCK_METHOD(bool, CheckUserExist, (int user_id), (const, override));
};

class MockICheckUserAccessToChat : public use_case::ICheckUserAccessToChat {
 public:
  MOCK_METHOD(bool,
              CheckUserAccessToChat,
              (int user_id, int chat_id),
              (const, override));
};

class MockICreateUser : public use_case::ICreateUser {
 public:
  MOCK_METHOD(entities::User, CreateUser, (int id), (const, override));
};

class MockISetChat : public use_case::ISetChat {
 public:
  MOCK_METHOD(void,
              SetChat,
              (std::vector<int> const& users, int chat_id),
              (const, override));
};

class MockICreateChat : public use_case::ICreateChat {
 public:
  MOCK_METHOD(int, CreateChat, (), (const, override));
};

class MockIGetMsgs : public use_case::IGetMsgs {
 public:
  MOCK_METHOD(std::vector<entities::Message>,
              GetMsgs,
              (int chat_id, time_t from_time),
              (const, override));
};

class MockISendMsg : public use_case::ISendMsg {
 public:
  MOCK_METHOD(void,
              SendMsg,
              (entities::Message const& msg, int chat_id),
              (const, override));
};

class MockIAnalysisText : public use_case::IAnalysisText {
 public:
  MOCK_METHOD(bool, AnalysisText, (std::string const& msg), (const, override));
};

}  // namespace calmgram::api_server::tests

#endif  // CALMGRAM_API_SERVER_USE_CASE_TEST_H