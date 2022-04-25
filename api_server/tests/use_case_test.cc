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
  // Выдаем исключение, что нужного пользователя не существует
  auto user_id(10);
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(user_id))
      .WillOnce(Throw(std::logic_error("No User")));
  // Ожидаем, что вызовется функция создания нового пользователя и вернёт нам
  // его с требуемыми данными
  entities::User user(user_id);
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
  // Ожидаем, что будет вызван метод GetUser, а в ответ мы вернем
  // подготовленного пользователя
  auto user_id(10);
  auto chats_cnt(5);
  std::vector<entities::Chat> user_chats;
  for (size_t i = 0; i < chats_cnt; ++i) {
    user_chats.push_back(entities::Chat(i));
  }
  entities::User user(user_id, user_chats);
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
  ASSERT_EQ(chats_res.size(), chats_cnt);
  for (size_t i = 0; i < chats_res.size(); ++i) {
    EXPECT_EQ(chats_res[i], user_chats[i].id);
  }
}

/**
 * @brief Тест успешного создания нового чата
 *
 */
TEST(AddChatUC, SuccessCreateChat) {
  // Ожидаем, что будет вызван GetUser дважды для проверки существования нужных
  // пользователей. Возвращаем, что они существуют
  std::vector<int> users_id(10, 20);
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(users_id[0], _));
  EXPECT_CALL(mock_get_user, GetUser(users_id[1], _))
      .Times(2)
      .WillRepeatedly(SetArgPointee<1>(true));
  // Ожидаем, что будет вызван метод CreateChat. Возвращаем подготовленный чат
  auto chat_id(123);
  entities::Chat new_chat(chat_id);
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
  // Ожидаем, что будет вызван GetUser для проверки существования нужных
  // пользователей. Возвращаем, что первого пользователя нет, а последующий не
  // будет проверен
  std::vector<int> users_id(10, 20);
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(users_id[0], _))
      .WillOnce(Throw(std::logic_error("Wrong User ID")));
  // Ожидаем, что метод CreateChat не будет вызван
  MockICreateChat mock_create_chat;
  EXPECT_CALL(mock_create_chat, CreateChat()).Times(0);
  // Ожидаем, что метод SetChat не будет вызван
  MockISetChat mock_set_chat;
  EXPECT_CALL(mock_set_chat, SetChat(_, _)).Times(0);
  // Запускаем сценарий добавления чата с ожиданием исключения
  EXPECT_THROW(use_case::AddChatUC(users_id, mock_get_user, mock_create_chat,
                                   mock_set_chat)
                   .Execute(),
               std::logic_error);
}

TEST(SendMsgUC, SuccessSendMsg) {
  // Ожидаем, что будет вызван GetUser для проверки существования нужного
  // пользователя. Возвращаем, что он существует
  auto user_id(10);
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(user_id, _))
      .WillOnce(SetArgPointee<1>(true));
  // Ожидаем, что анализ текста вернет false
  entities::Content content("qwerty", entities::TEXT);
  auto mark = false;
  MockIAnalysisText mock_analisis_text;
  EXPECT_CALL(mock_analisis_text, AnalysisText(content.data))
      .WillOnce(Return(mark));
  // Ожидаем, что будет вызван метод SendMsg с подготовленным сообщением
  entities::Message message{
      .owner_id = user_id, .content = content, .is_marked = mark};
  auto chat_id(123);
  MockISendMsg mock_send_msg;
  EXPECT_CALL(mock_send_msg, SendMsg(message, chat_id)).Times(1);
  // Запускаем сценарий отправки сообщения
  use_case::SendMsgUC(user_id, chat_id, content, mock_get_user,
                      mock_analisis_text, mock_send_msg)
      .Execute();
}

/**
 * @brief Тест создания нового чата с несуществующим пользователем
 *
 */
TEST(SendMsgUC, WrongUserID) {
  // Ожидаем, что будет вызван GetUser для проверки существования нужного
  // пользователя. Возвращаем, что пользователя нет
  auto user_id(10);
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(user_id, _))
      .WillOnce(Throw(std::logic_error("Wrong User ID")));
  // Ожидаем, что метод AnalysisText не будет вызван
  MockIAnalysisText mock_analisis_text;
  EXPECT_CALL(mock_analisis_text, AnalysisText(_)).Times(0);
  // Ожидаем, что метод SendMsg не будет вызван
  MockISendMsg mock_send_msg;
  EXPECT_CALL(mock_send_msg, SendMsg(_, _)).Times(0);
  // Запускаем сценарий отправки сообщения с ожиданием исключения
  EXPECT_THROW(
      {
        auto chat_id(123);
        entities::Content content("qwerty", entities::TEXT);
        use_case::SendMsgUC(user_id, chat_id, content, mock_get_user,
                            mock_analisis_text, mock_send_msg)
            .Execute();
      },
      std::logic_error);
}

TEST(UpdateChatUC, SuccessUpdateChat) {
  // Ожидаем, что будет вызван GetUser для проверки существования нужного
  // пользователя. Возвращаем, что он существует
  auto user_id(10);
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(user_id, _))
      .WillOnce(SetArgPointee<1>(true));
  // Ожидаем, что будет вызван метод GetMsgs. Возвращаем подготовленный список
  // сообщений
  auto chat_id(123);
  time_t from_time(1000);
  size_t msg_cnt = 10;
  std::vector<entities::Message> msgs;
  // Неподходящие сообщения
  for (size_t i = 0; i < msg_cnt; ++i) {
    auto user_id_tmp = (i > msg_cnt / 2) ? 10 : 20;
    entities::Content content_tmp("qwerty" + std::to_string(i), entities::TEXT);
    time_t from_time_tmp = (from_time / 2) + i;
    auto mark_tmp = (i > msg_cnt / 2) ? true : false;
    msgs.push_back({user_id_tmp, from_time_tmp, content_tmp, mark_tmp});
  }
  // Подходящие сообщения
  for (size_t i = 0; i < msg_cnt; ++i) {
    auto user_id_tmp = (i > msg_cnt / 2) ? 10 : 20;
    entities::Content content_tmp("qwerty" + std::to_string(i), entities::TEXT);
    time_t from_time_tmp = (from_time * 2) + i;
    auto mark_tmp = (i > msg_cnt / 2) ? true : false;
    msgs.push_back({user_id_tmp, from_time_tmp, content_tmp, mark_tmp});
  }
  MockIGetMsgs mock_get_msgs;
  EXPECT_CALL(mock_get_msgs, GetMsgs(chat_id, from_time))
      .WillOnce(Return(msgs));
  // Запускаем сценарий получения последних сообщений
  std::vector<entities::Message> msgs_res =
      use_case::UpdateChatUC(user_id, chat_id, from_time, mock_get_user,
                             mock_get_msgs)
          .Execute();
  // В результате мы должны получит список сообщений, от передоного времени
  ASSERT_EQ(msgs_res.size(), msg_cnt);
  for (size_t i = 0; i < msgs_res.size(); ++i) {
    EXPECT_EQ(msgs_res[i], msgs[i + msg_cnt]);
  }
}

TEST(UpdateChatUC, WrongUserID) {
  // Ожидаем, что будет вызван GetUser для проверки существования нужного
  // пользователя. Возвращаем, что пользователя нет
  auto user_id(10);
  MockIGetUser mock_get_user;
  EXPECT_CALL(mock_get_user, GetUser(user_id, _))
      .WillOnce(Throw(std::logic_error("Wrong User ID")));
  // Ожидаем, что метод GetMsgs не будет вызван
  MockIGetMsgs mock_get_msgs;
  EXPECT_CALL(mock_get_msgs, GetMsgs(_, _)).Times(0);
  // Запускаем сценарий получения последних сообщений с ожиданием исключения
  EXPECT_THROW(
      {
        auto chat_id(123);
        time_t from_time(1000);
        std::vector<entities::Message> msgs_res =
            use_case::UpdateChatUC(user_id, chat_id, from_time, mock_get_user,
                                   mock_get_msgs)
                .Execute();
      },
      std::logic_error);
}

}  // namespace calmgram::api_server::tests