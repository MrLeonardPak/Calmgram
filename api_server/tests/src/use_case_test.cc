/**
 * lcov -t "tests/tests_kmeans" -o coverage.info -c -d kmeans_libs/
 * genhtml -o report coverage.info
 * cd report && python3 -m http.server 8000
 */

#include "use_case_test.h"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;
using ::testing::Truly;

namespace calmgram::api_server::tests {

/**
 * @brief Тест авторизации нового пользователя с последующим созданием нового
 * пользователя
 *
 */
TEST(UserAuthUC, ForNewUser) {
  // Выдаем исключение, что нужного пользователя не существует
  auto user_id(10);
  auto mock_get_user = std::make_shared<const MockIGetUser>();
  EXPECT_CALL(*mock_get_user, GetUser(user_id))
      .WillOnce(Throw(std::logic_error("No User")));
  // Ожидаем, что вызовется функция создания нового пользователя и вернёт нам
  // его с требуемыми данными
  entities::User user(user_id);
  auto mock_creat_user = std::make_shared<const MockICreateUser>();
  EXPECT_CALL(*mock_creat_user, CreateUser(user_id)).WillOnce(Return(user));
  // Запускаем сценарий авторизации пользователя
  std::vector<int> chats =
      use_case::UserAuthUC(mock_get_user, mock_creat_user).Execute(user_id);
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
  auto mock_get_user = std::make_shared<const MockIGetUser>();
  EXPECT_CALL(*mock_get_user, GetUser(user_id)).WillOnce(Return(user));
  // Ожидаем, что метод CreateUser не будет вызван
  auto mock_creat_user = std::make_shared<const MockICreateUser>();
  EXPECT_CALL(*mock_creat_user, CreateUser(_)).Times(0);
  // Запускаем сценарий авторизации пользователя
  std::vector<int> chats_res =
      use_case::UserAuthUC(mock_get_user, mock_creat_user).Execute(user_id);
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
  std::vector<int> users_id{10, 20};
  auto mock_check_user = std::make_shared<const MockICheckUser>();
  EXPECT_CALL(*mock_check_user, CheckUser(users_id[0]));
  EXPECT_CALL(*mock_check_user, CheckUser(users_id[1]));
  // Ожидаем, что будет вызван метод CreateChat. Возвращаем подготовленный чат
  auto chat_id(123);
  auto mock_create_chat = std::make_shared<const MockICreateChat>();
  EXPECT_CALL(*mock_create_chat, CreateChat()).WillOnce(Return(chat_id));
  // Ожидаем, что будет вызван метод SetChat
  auto mock_set_chat = std::make_shared<const MockISetChat>();
  EXPECT_CALL(*mock_set_chat, SetChat(users_id, chat_id)).Times(1);
  // Запускаем сценарий добавления чата
  int chat_id_res =
      use_case::AddChatUC(mock_check_user, mock_create_chat, mock_set_chat)
          .Execute(users_id);
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
  std::vector<int> users_id{10, 20};
  auto mock_check_user = std::make_shared<const MockICheckUser>();
  EXPECT_CALL(*mock_check_user, CheckUser(users_id[0]))
      .WillOnce(Throw(std::logic_error("Wrong User ID")));
  // Ожидаем, что метод CreateChat не будет вызван
  auto mock_create_chat = std::make_shared<const MockICreateChat>();
  EXPECT_CALL(*mock_create_chat, CreateChat()).Times(0);
  // Ожидаем, что метод SetChat не будет вызван
  auto mock_set_chat = std::make_shared<const MockISetChat>();
  EXPECT_CALL(*mock_set_chat, SetChat(_, _)).Times(0);
  // Запускаем сценарий добавления чата с ожиданием исключения
  EXPECT_THROW(
      use_case::AddChatUC(mock_check_user, mock_create_chat, mock_set_chat)
          .Execute(users_id),
      std::logic_error);
}

/**
 * @brief Тест успешной отправки сообщения в чат
 *
 */
TEST(SendMsgUC, SuccessSendMsg) {
  // Ожидаем, что будет вызван GetUser для проверки существования нужного
  // пользователя. Возвращаем, что он существует
  auto user_id(10);
  auto mock_check_user = std::make_shared<const MockICheckUser>();
  EXPECT_CALL(*mock_check_user, CheckUser(user_id));
  // Ожидаем, что анализ текста вернет false
  entities::Content content("qwerty", entities::TEXT);
  auto mark = false;
  auto mock_analisis_text = std::make_shared<const MockIAnalysisText>();
  EXPECT_CALL(*mock_analisis_text, AnalysisText(content.text))
      .WillOnce(Return(mark));
  // Ожидаем, что будет вызван метод SendMsg с подготовленным сообщением
  entities::Message message{
      .owner_id = user_id, .content = content, .is_marked = mark};
  auto chat_id(123);
  auto check_msg = [message](entities::Message const& msg) {
    return std::tie(message.owner_id, message.content, message.is_marked) ==
           std::tie(msg.owner_id, msg.content, msg.is_marked);
  };
  auto mock_send_msg = std::make_shared<const MockISendMsg>();
  EXPECT_CALL(*mock_send_msg, SendMsg(Truly(check_msg), chat_id)).Times(1);
  // Запускаем сценарий отправки сообщения
  use_case::SendMsgUC(mock_check_user, mock_analisis_text, mock_send_msg)
      .Execute(user_id, chat_id, content);
}

/**
 * @brief Тест отправки сообщения от несуществующего пользователя
 *
 */
TEST(SendMsgUC, WrongUserID) {
  // Ожидаем, что будет вызван GetUser для проверки существования нужного
  // пользователя. Возвращаем, что пользователя нет
  auto user_id(10);
  auto mock_check_user = std::make_shared<const MockICheckUser>();
  EXPECT_CALL(*mock_check_user, CheckUser(user_id))
      .WillOnce(Throw(std::logic_error("Wrong User ID")));
  // Ожидаем, что метод AnalysisText не будет вызван
  auto mock_analisis_text = std::make_shared<const MockIAnalysisText>();
  EXPECT_CALL(*mock_analisis_text, AnalysisText(_)).Times(0);
  // Ожидаем, что метод SendMsg не будет вызван
  auto mock_send_msg = std::make_shared<const MockISendMsg>();
  EXPECT_CALL(*mock_send_msg, SendMsg(_, _)).Times(0);
  // Запускаем сценарий отправки сообщения с ожиданием исключения
  EXPECT_THROW(
      {
        auto chat_id(123);
        entities::Content content("qwerty", entities::TEXT);
        use_case::SendMsgUC(mock_check_user, mock_analisis_text, mock_send_msg)
            .Execute(user_id, chat_id, content);
      },
      std::logic_error);
}

/**
 * @brief Тест успешного обновления чата
 *
 */
TEST(UpdateChatUC, SuccessUpdateChat) {
  // Ожидаем, что будет вызван GetUser для проверки существования нужного
  // пользователя. Возвращаем, что он существует
  auto user_id(10);
  auto mock_check_user = std::make_shared<const MockICheckUser>();
  EXPECT_CALL(*mock_check_user, CheckUser(user_id));
  // Ожидаем, что будет вызван метод GetMsgs. Возвращаем подготовленный список
  // сообщений
  auto chat_id(123);
  time_t from_time(1000);
  size_t msg_cnt = 10;
  std::vector<entities::Message> msgs;
  // Подходящие сообщения
  for (size_t i = 0; i < msg_cnt; ++i) {
    auto user_id_tmp = (i > msg_cnt / 2) ? 10 : 20;
    entities::Content content_tmp("qwerty" + std::to_string(i), entities::TEXT);
    time_t from_time_tmp = from_time + i;
    auto mark_tmp = (i > msg_cnt / 2) ? true : false;
    msgs.push_back({user_id_tmp, from_time_tmp, content_tmp, mark_tmp});
  }
  auto mock_get_msgs = std::make_shared<const MockIGetMsgs>();
  EXPECT_CALL(*mock_get_msgs, GetMsgs(chat_id, from_time))
      .WillOnce(Return(msgs));
  // Запускаем сценарий получения последних сообщений
  std::vector<entities::Message> msgs_res =
      use_case::UpdateChatUC(mock_check_user, mock_get_msgs)
          .Execute(user_id, chat_id, from_time);
  // В результате мы должны получит список сообщений, от передоного времени
  ASSERT_EQ(msgs_res.size(), msg_cnt);
  for (size_t i = 0; i < msgs_res.size(); ++i) {
    EXPECT_EQ(msgs_res[i], msgs[i]);
  }
}

/**
 * @brief Тест обновления чата несуществующим пользователем
 *
 */
TEST(UpdateChatUC, WrongUserID) {
  // Ожидаем, что будет вызван GetUser для проверки существования нужного
  // пользователя. Возвращаем, что пользователя нет
  auto user_id(10);
  auto mock_check_user = std::make_shared<const MockICheckUser>();
  EXPECT_CALL(*mock_check_user, CheckUser(user_id))
      .WillOnce(Throw(std::logic_error("Wrong User ID")));
  // Ожидаем, что метод GetMsgs не будет вызван
  auto mock_get_msgs = std::make_shared<const MockIGetMsgs>();
  EXPECT_CALL(*mock_get_msgs, GetMsgs(_, _)).Times(0);
  // Запускаем сценарий получения последних сообщений с ожиданием исключения
  EXPECT_THROW(
      {
        auto chat_id(123);
        time_t from_time(1000);
        std::vector<entities::Message> msgs_res =
            use_case::UpdateChatUC(mock_check_user, mock_get_msgs)
                .Execute(user_id, chat_id, from_time);
      },
      std::logic_error);
}

}  // namespace calmgram::api_server::tests