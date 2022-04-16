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

#include <exception>

using ::testing::_;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::Throw;

namespace use_case = ::calmgram::api_server::use_case;
namespace entities = ::calmgram::api_server::entities;

class MockIGetUser : public use_case::IGetUser {
 public:
  MOCK_METHOD(entities::User, GetUser, (int id), (override));
  MOCK_METHOD(void, GetUser, (int id, bool* is_exist), (override));
};

class MockICreateUser : public use_case::ICreateUser {
 public:
  MOCK_METHOD(entities::User, CreateUser, (), (override));
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

TEST(UserAuthUC, ForNewUser) {
  int user_id = 10;
  entities::User user(user_id);

  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(user_id))
      .WillOnce(Throw(std::logic_error("No User")));

  MockICreateUser mock_creat_user;
  EXPECT_CALL(mock_creat_user, CreateUser()).WillOnce(Return(user));

  std::vector<int> chats =
      use_case::UserAuthUC(user_id, mock_get_user, mock_creat_user).Execute();
  EXPECT_TRUE(chats.empty());
}

TEST(UserAuthUC, ForOldUser) {
  int user_id = 10;
  int chats_cnt = 5;
  std::vector<entities::Chat> chats_in;
  for (size_t i = 0; i < chats_cnt; ++i) {
    chats_in.push_back(entities::Chat(i));
  }
  entities::User user(user_id, chats_in);

  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(user_id)).WillOnce(Return(user));

  MockICreateUser mock_creat_user;
  EXPECT_CALL(mock_creat_user, CreateUser()).Times(0);

  std::vector<int> chats_id =
      use_case::UserAuthUC(user_id, mock_get_user, mock_creat_user).Execute();
  for (size_t i = 0; i < chats_cnt; ++i) {
    EXPECT_EQ(chats_id[i], chats_in[i].id);
  }
}

TEST(AddChatUC, SuccessCreateChat) {
  std::vector<int> users_id = {10, 20};
  int chat_id = 123;
  entities::Chat new_chat(chat_id);

  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(users_id[0], _));
  EXPECT_CALL(mock_get_user, GetUser(users_id[1], _))
      .Times(2)
      .WillRepeatedly(SetArgPointee<1>(true));

  MockICreateChat mock_create_chat;
  EXPECT_CALL(mock_create_chat, CreateChat()).WillOnce(Return(new_chat));

  MockISetChat mock_set_chat;
  EXPECT_CALL(mock_set_chat, SetChat(users_id, chat_id)).Times(1);

  int chat_id_out = use_case::AddChatUC(users_id, mock_get_user,
                                        mock_create_chat, mock_set_chat)
                        .Execute();

  EXPECT_EQ(chat_id_out, chat_id);
}

TEST(AddChatUC, WrongUserID) {
  std::vector<int> users_id = {10, 20};
  std::vector<entities::User> users;
  users.push_back(entities::User(users_id[0]));
  users.push_back(entities::User(users_id[1]));
  int chat_id = 123;
  entities::Chat new_chat(chat_id);

  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(users_id[0], _));
  EXPECT_CALL(mock_get_user, GetUser(users_id[1], _))
      .Times(2)
      .WillOnce(SetArgPointee<1>(true))
      .WillOnce(Throw(std::logic_error("Wrong User ID")));

  MockICreateChat mock_create_chat;
  EXPECT_CALL(mock_create_chat, CreateChat()).Times(0);

  MockISetChat mock_set_chat;
  EXPECT_CALL(mock_set_chat, SetChat(_, _)).Times(0);

  int chat_id_out = use_case::AddChatUC(users_id, mock_get_user,
                                        mock_create_chat, mock_set_chat)
                        .Execute();

  EXPECT_EQ(chat_id_out, -1);
}