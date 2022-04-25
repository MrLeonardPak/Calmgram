/**
 * lcov -t "tests/tests_kmeans" -o coverage.info -c -d kmeans_libs/
 * genhtml -o report coverage.info
 * cd report && python3 -m http.server 8000
 */

#include "use_case_test.h"

#include <exception>

namespace calmgram::api_server::tests {

using ::testing::_;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::Throw;

/**
 * @brief Тест авторизации нового пользователя с последующим созданием нового
 * пользователя
 *
 */
TEST(UserAuthUC, ForNewUser) {
  auto user_id(10);
  entities::User user(user_id);
  // Выдаем исключение, что нужного пользователя не существует
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(user_id))
      .WillOnce(Throw(std::logic_error("No User")));
  // Ожидаем, что вызовется функция создания нового пользователя и вернёт нам
  // его с требуемыми данными
  MockICreateUser mock_creat_user;
  EXPECT_CALL(mock_creat_user, CreateUser(user_id)).WillOnce(Return(user));
  // Запускаем сценарий авторизации пользователя
  std::vector<int> chats =
      use_case::UserAuthUC(user_id, mock_get_user, mock_creat_user).Execute();
  // Для нового пользователя ожидается, что список чатов будет пустым
  EXPECT_TRUE(chats.empty());
}

/**
 * @brief Тест авторизации уже существующего пользователя
 *
 */
TEST(UserAuthUC, ForOldUser) {
  // Подготавливаем пользователя со списком чатов
  auto user_id(10);
  auto chats_cnt(5);
  std::vector<entities::Chat> user_chats;
  for (size_t i = 0; i < chats_cnt; ++i) {
    user_chats.push_back(entities::Chat(i));
  }
  entities::User user(user_id, user_chats);
  // Ожидаем, что будет вызван метод GetUser, а в ответ мы вернем
  // подготовленного пользователя
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(user_id)).WillOnce(Return(user));
  // Ожидаем, что метод CreateUser не будет вызван
  MockICreateUser mock_creat_user;
  EXPECT_CALL(mock_creat_user, CreateUser(_)).Times(0);
  // Запускаем сценарий авторизации пользователя
  std::vector<int> chats_res =
      use_case::UserAuthUC(user_id, mock_get_user, mock_creat_user).Execute();
  // В результате мы должны получит список чатов (только id), совпадающий с
  // подготовленным списком по id
  for (size_t i = 0; i < chats_res.size(); ++i) {
    EXPECT_EQ(chats_res[i], user_chats[i].id);
  }
}

/**
 * @brief Тест успешного создания нового чата
 *
 */
TEST(AddChatUC, SuccessCreateChat) {
  std::vector<int> users_id(10, 20);
  auto chat_id(123);
  entities::Chat new_chat(chat_id);
  // Ожидаем, что будет вызван GetUser дважды для проверки существования нужных
  // пользователей. Возвращаем, что они существуют
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(users_id[0], _));
  EXPECT_CALL(mock_get_user, GetUser(users_id[1], _))
      .Times(2)
      .WillRepeatedly(SetArgPointee<1>(true));
  // Ожидаем, что будет вызван метод CreateChat. Возвращаем подготовленный чат
  MockICreateChat mock_create_chat;
  EXPECT_CALL(mock_create_chat, CreateChat()).WillOnce(Return(new_chat));
  // Ожидаем, что будет вызван метод SetChat
  MockISetChat mock_set_chat;
  EXPECT_CALL(mock_set_chat, SetChat(users_id, chat_id)).Times(1);
  // Запускаем сценарий добавления чата
  int chat_id_res = use_case::AddChatUC(users_id, mock_get_user,
                                        mock_create_chat, mock_set_chat)
                        .Execute();
  // В результате должны совпадать id чата
  EXPECT_EQ(chat_id_res, chat_id);
}

/**
 * @brief Тест создания нового чата с несуществующим пользователем
 *
 */
TEST(AddChatUC, WrongUserID) {
  std::vector<int> users_id = {10, 20};
  int chat_id = 123;
  entities::Chat new_chat(chat_id);
  // Ожидаем, что будет вызван GetUser дважды для проверки существования нужных
  // пользователей. Возвращаем, что существуют только первый пользователь
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(users_id[0], _));
  EXPECT_CALL(mock_get_user, GetUser(users_id[1], _))
      .Times(2)
      .WillOnce(SetArgPointee<1>(true))
      .WillOnce(Throw(std::logic_error("Wrong User ID")));
  // Ожидаем, что метод CreateChat не будет вызван
  MockICreateChat mock_create_chat;
  EXPECT_CALL(mock_create_chat, CreateChat()).Times(0);
  // Ожидаем, что метод SetChat не будет вызван
  MockISetChat mock_set_chat;
  EXPECT_CALL(mock_set_chat, SetChat(_, _)).Times(0);
  // Запускаем сценарий добавления чата
  int chat_id_res = use_case::AddChatUC(users_id, mock_get_user,
                                        mock_create_chat, mock_set_chat)
                        .Execute();
  // В результате больжен быть id == -1
  EXPECT_EQ(chat_id_res, -1);
}

}  // namespace calmgram::api_server::tests