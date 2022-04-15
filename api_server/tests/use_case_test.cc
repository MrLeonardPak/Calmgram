/**
 * lcov -t "tests/tests_kmeans" -o coverage.info -c -d kmeans_libs/
 * genhtml -o report coverage.info
 * cd report && python3 -m http.server 8000
 */
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "add_chat_uc.h"
#include "interfaces_use_case.h"
#include "send_msg_uc.h"
#include "update_chat_uc.h"
#include "user_auth_uc.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;

namespace use_case = ::calmgram::api_server::use_case;
namespace entities = ::calmgram::api_server::entities;

class MockIGetUser : public use_case::IGetUser {
 public:
  MOCK_METHOD(entities::User, GetUser, (int id), (override));
};

class MockICreateUser : public use_case::ICreateUser {
 public:
  MOCK_METHOD(int, CreateUser, (), (override));
};

TEST(USE_CASE, User_Auth) {
  MockICreateUser mock_creat_user;
  EXPECT_CALL(mock_creat_user, CreateUser()).WillOnce(Return(123));

  MockIGetUser mock_get_user;
  entities::User user;
  EXPECT_CALL(mock_get_user, GetUser(0)).WillOnce(Return(user));

  use_case::UserAuthUC use_case(0, mock_get_user, mock_creat_user);
}