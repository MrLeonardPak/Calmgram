#ifndef CALMGRAM_API_SERVER_USE_CASE_TEST_H
#define CALMGRAM_API_SERVER_USE_CASE_TEST_H

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "add_chat_uc.h"
#include "user_auth_uc.h"

namespace calmgram::api_server::tests {

namespace use_case = ::calmgram::api_server::use_case;
namespace entities = ::calmgram::api_server::entities;

class MockIGetUser : public use_case::IGetUser {
 public:
  MOCK_METHOD(entities::User, GetUser, (int id), (override));
  MOCK_METHOD(void, GetUser, (int id, bool* is_exist), (override));
};

class MockICreateUser : public use_case::ICreateUser {
 public:
  MOCK_METHOD(entities::User, CreateUser, (int const& id), (override));
};

class MockISetChat : public use_case::ISetChat {
 public:
  MOCK_METHOD(void, SetChat, (std::vector<int> users, int chat_id), (override));
};

class MockICreateChat : public use_case::ICreateChat {
 public:
  MOCK_METHOD(entities::Chat, CreateChat, (), (override));
};

class MockIGetMsgs : public use_case::IGetMsgs {
 public:
  MOCK_METHOD(std::vector<entities::Message>,
              GetMsgs,
              (int chat_id, time_t from_time),
              (override));
};

class MockISendMsg : public use_case::ISendMsg {
 public:
  MOCK_METHOD(entities::Chat,
              SendMsg,
              (entities::Message const& msg, int chat_id),
              (override));
};

class MockIAnalysisText : public use_case::IAnalysisText {
 public:
  MOCK_METHOD(bool, AnalysisText, (std::string const& msg), (override));
};

}  // namespace calmgram::api_server::tests

#endif  // CALMGRAM_API_SERVER_USE_CASE_TEST_H