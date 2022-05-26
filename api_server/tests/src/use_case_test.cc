#include "use_case_test.h"

#include "add_chat_uc.h"
#include "add_to_dataset_uc.h"
#include "get_chat_list_uc.h"
#include "send_msg_uc.h"
#include "update_chat_uc.h"
#include "user_auth_uc.h"

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
  // Возвращаем, что нужного пользователя не существует
  auto login = std::string("login");
  auto password = std::string("password");
  auto mock_check_user = std::make_shared<MockICheckUser const>();
  EXPECT_CALL(*mock_check_user, CheckUser(login, password))
      .WillOnce(Return(false));
  // Успешно создаем пользователя
  auto mock_creat_user = std::make_shared<MockICreateUser const>();
  EXPECT_CALL(*mock_creat_user, CreateUser(login, password))
      .WillOnce(Return(true));
  // Создаем новую сессию
  auto token = std::string("token");
  auto mock_create_session = std::make_unique<MockICreateSession>();
  EXPECT_CALL(*mock_create_session, CreateSession("login"))
      .WillOnce(Return(token));
  // Запускаем сценарий авторизации пользователя
  std::string res = use_case::UserAuthUC(mock_check_user, mock_creat_user,
                                         std::move(mock_create_session))
                        .Execute(login, password);
  // Проверяем совпадение токенов
  EXPECT_EQ(res, token);
}

/**
 * @brief Тест авторизации уже существующего пользователя
 *
 */
TEST(UserAuthUC, ForOldUser) {
  // Возвращаем, что вход успешный
  auto login = std::string("login");
  auto password = std::string("password");
  auto mock_check_user = std::make_shared<MockICheckUser const>();
  EXPECT_CALL(*mock_check_user, CheckUser(login, password))
      .WillOnce(Return(true));
  // метод CreateUser не будет вызван
  auto mock_creat_user = std::make_shared<MockICreateUser const>();
  EXPECT_CALL(*mock_creat_user, CreateUser(_, _)).Times(0);
  // Создаем новую сессию
  auto token = std::string("token");
  auto mock_create_session = std::make_unique<MockICreateSession>();
  EXPECT_CALL(*mock_create_session, CreateSession("login"))
      .WillOnce(Return(token));
  // Запускаем сценарий авторизации пользователя
  std::string res = use_case::UserAuthUC(mock_check_user, mock_creat_user,
                                         std::move(mock_create_session))
                        .Execute(login, password);
  // Проверяем совпадение токенов
  EXPECT_EQ(res, token);
}

/**
 * @brief Тест успешного создания нового чата
 *
 */
TEST(AddChatUC, SuccessCreateChat) {
  // Запрос со существующей сессии
  auto token = std::string("token");
  auto login = std::string("login");
  auto mock_get_session_login = std::make_shared<MockIGetSessionLogin const>();
  EXPECT_CALL(*mock_get_session_login, GetSessionLogin(token))
      .WillOnce(Return(login));
  // Успешно проверим всех пользоваетлей на существование
  auto users_logins = std::vector<std::string_view>{"anna", "leo"};
  auto mock_check_user = std::make_shared<MockICheckUser const>();
  EXPECT_CALL(*mock_check_user, CheckUser(users_logins[0]))
      .WillOnce(Return(true));
  EXPECT_CALL(*mock_check_user, CheckUser(users_logins[1]))
      .WillOnce(Return(true));
  // Создаем новый чат со всеми
  auto chat_id = 123;
  auto user_login_update =
      std::vector<std::string_view>{"anna", "leo", "login"};
  auto mock_create_chat = std::make_shared<MockICreateChat const>();
  EXPECT_CALL(*mock_create_chat, CreateChat(user_login_update))
      .WillOnce(Return(chat_id));
  // Запускаем сценарий добавления чата
  int res = use_case::AddChatUC(mock_get_session_login, mock_check_user,
                                mock_create_chat)
                .Execute(token, users_logins);
  // В результате должны совпадать id чата
  EXPECT_EQ(res, chat_id);
}

/**
 * @brief Тест создания нового чата с несуществующим пользователем
 *
 */
TEST(AddChatUC, WrongUserID) {
  // Запрос со существующей сессии
  auto token = std::string("token");
  auto login = std::string("login");
  auto mock_get_session_login = std::make_shared<MockIGetSessionLogin const>();
  EXPECT_CALL(*mock_get_session_login, GetSessionLogin(token))
      .WillOnce(Return(login));
  // Одного пользователя не существует
  auto users_logins = std::vector<std::string_view>{"anna", "leo"};
  auto mock_check_user = std::make_shared<MockICheckUser const>();
  EXPECT_CALL(*mock_check_user, CheckUser(users_logins[0]))
      .WillOnce(Return(false));
  // Чат создаваться не будет
  auto mock_create_chat = std::make_shared<MockICreateChat const>();
  EXPECT_CALL(*mock_create_chat, CreateChat(_)).Times(0);
  // Запускаем сценарий добавления чата с ожиданием исключения
  EXPECT_THROW(use_case::AddChatUC(mock_get_session_login, mock_check_user,
                                   mock_create_chat)
                   .Execute(token, users_logins),
               std::runtime_error);
}

/**
 * @brief Тест успешной отправки сообщения в чат
 *
 */
TEST(SendMsgUC, SuccessSendMsg) {
  // Запрос со существующей сессии
  auto token = std::string("token");
  auto login = std::string("login");
  auto mock_get_session_login = std::make_shared<MockIGetSessionLogin const>();
  EXPECT_CALL(*mock_get_session_login, GetSessionLogin(token))
      .WillOnce(Return(login));
  // У пользователя есть доступ к чату
  auto chat_id = 123;
  auto mock_check_user = std::make_shared<MockICheckUserAccessToChat const>();
  EXPECT_CALL(*mock_check_user, CheckUserAccessToChat(login, chat_id))
      .WillOnce(Return(true));
  // Анализ текста вернет false
  auto content = entities::Content("qwerty");
  auto mark = false;
  auto mock_analisis_text = std::make_shared<MockIAnalysisText const>();
  EXPECT_CALL(*mock_analisis_text, AnalysisText(content.text))
      .WillOnce(Return(mark));
  // Ожидаем, что будет вызван метод SendMsg с подготовленным сообщением
  auto message = entities::Message(login, 0, content, mark);
  auto check_msg = [message](entities::Message const& msg) {
    return std::tie(message.owner_login, message.content, message.is_marked) ==
           std::tie(msg.owner_login, msg.content, msg.is_marked);
  };
  auto mock_send_msg = std::make_shared<MockISendMsg const>();
  EXPECT_CALL(*mock_send_msg, SendMsg(Truly(check_msg), chat_id)).Times(1);
  // Запускаем сценарий отправки сообщения
  use_case::SendMsgUC(mock_get_session_login, mock_check_user,
                      mock_analisis_text, mock_send_msg)
      .Execute(token, chat_id, content);
}

/**
 * @brief Тест отправки сообщения от несуществующего пользователя
 *
 */
TEST(SendMsgUC, WrongUserID) {
  // Запрос со существующей сессии
  auto token = std::string("token");
  auto login = std::string("login");
  auto mock_get_session_login = std::make_shared<MockIGetSessionLogin const>();
  EXPECT_CALL(*mock_get_session_login, GetSessionLogin(token))
      .WillOnce(Return(login));
  // У пользоваетля нет доступа к чату
  auto chat_id = 123;
  auto mock_check_user = std::make_shared<MockICheckUserAccessToChat const>();
  EXPECT_CALL(*mock_check_user, CheckUserAccessToChat(login, chat_id))
      .WillOnce(Return(false));
  // AnalysisText не будет вызван
  auto mock_analisis_text = std::make_shared<MockIAnalysisText const>();
  EXPECT_CALL(*mock_analisis_text, AnalysisText(_)).Times(0);
  // Ожидаем, что метод SendMsg не будет вызван
  auto mock_send_msg = std::make_shared<MockISendMsg const>();
  EXPECT_CALL(*mock_send_msg, SendMsg(_, _)).Times(0);
  // Запускаем сценарий отправки сообщения с ожиданием исключения
  EXPECT_THROW(
      {
        entities::Content content("qwerty");
        use_case::SendMsgUC(mock_get_session_login, mock_check_user,
                            mock_analisis_text, mock_send_msg)
            .Execute(token, chat_id, content);
      },
      std::runtime_error);
}

/**
 * @brief Тест успешного обновления чата
 *
 */
TEST(UpdateChatUC, SuccessUpdateChat) {
  // Запрос со существующей сессии
  auto token = std::string("token");
  auto login = std::string("login");
  auto mock_get_session_login = std::make_shared<MockIGetSessionLogin const>();
  EXPECT_CALL(*mock_get_session_login, GetSessionLogin(token))
      .WillOnce(Return(login));
  // У пользователя есть доступ к чату
  auto chat_id = 123;
  auto mock_check_user = std::make_shared<MockICheckUserAccessToChat const>();
  EXPECT_CALL(*mock_check_user, CheckUserAccessToChat(login, chat_id))
      .WillOnce(Return(true));
  // Отдаем список свежих сообщений
  time_t from_time(1000);
  size_t msg_cnt = 10;
  std::vector<entities::Message> msgs;
  // Подходящие сообщения
  for (size_t i = 0; i < msg_cnt; ++i) {
    auto user_login_tmp = (i > msg_cnt / 2) ? "anna" : "leo";
    entities::Content content_tmp("qwerty" + std::to_string(i));
    time_t from_time_tmp = from_time + i;
    auto mark_tmp = (i > msg_cnt / 2) ? true : false;
    msgs.push_back({user_login_tmp, from_time_tmp, content_tmp, mark_tmp});
  }
  auto mock_get_msgs = std::make_shared<MockIGetMsgs const>();
  EXPECT_CALL(*mock_get_msgs, GetMsgs(chat_id, from_time))
      .WillOnce(Return(msgs));
  // Запускаем сценарий получения последних сообщений
  std::vector<entities::Message> msgs_res =
      use_case::UpdateChatUC(mock_get_session_login, mock_check_user,
                             mock_get_msgs)
          .Execute(token, chat_id, from_time);
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
  // Запрос со существующей сессии
  auto token = std::string("token");
  auto login = std::string("login");
  auto mock_get_session_login = std::make_shared<MockIGetSessionLogin const>();
  EXPECT_CALL(*mock_get_session_login, GetSessionLogin(token))
      .WillOnce(Return(login));
  // У пользователя нет доступ к чату
  auto chat_id = 123;
  auto mock_check_user = std::make_shared<MockICheckUserAccessToChat const>();
  EXPECT_CALL(*mock_check_user, CheckUserAccessToChat(login, chat_id))
      .WillOnce(Return(false));
  // Ожидаем, что метод GetMsgs не будет вызван
  auto mock_get_msgs = std::make_shared<MockIGetMsgs const>();
  EXPECT_CALL(*mock_get_msgs, GetMsgs(_, _)).Times(0);
  // Запускаем сценарий получения последних сообщений с ожиданием исключения
  EXPECT_THROW(
      {
        time_t from_time(1000);
        std::vector<entities::Message> msgs_res =
            use_case::UpdateChatUC(mock_get_session_login, mock_check_user,
                                   mock_get_msgs)
                .Execute(token, chat_id, from_time);
      },
      std::runtime_error);
}

/**
 * @brief Тест получения списка чатов
 *
 */
TEST(GetChatListUC, SuccessGetChatList) {
  // Запрос со существующей сессии
  auto token = std::string("token");
  auto login = std::string("login");
  auto mock_get_session_login = std::make_shared<MockIGetSessionLogin const>();
  EXPECT_CALL(*mock_get_session_login, GetSessionLogin(token))
      .WillOnce(Return(login));
  // Возвращаем список доступных чатов
  auto chat_ids = std::vector<int>{1, 2};
  auto mock_getter_chat_list = std::make_shared<MockIGetChatList const>();
  EXPECT_CALL(*mock_getter_chat_list, GetChatList(login))
      .WillOnce(Return(chat_ids));
  // Возвращаем список пользователей в каждом чате
  auto users_login = std::vector<std::string>{"login", "anna"};
  auto mock_get_user_list = std::make_shared<MockIGetUserListFromChat const>();
  EXPECT_CALL(*mock_get_user_list, GetUserListFromChat(chat_ids[0]))
      .WillOnce(Return(users_login));
  std::reverse(users_login.begin(), users_login.end());
  EXPECT_CALL(*mock_get_user_list, GetUserListFromChat(chat_ids[1]))
      .WillOnce(Return(users_login));

  // Запускаем сценарий
  auto chats = std::vector<entities::Chat>{{chat_ids[0], {"anna"}},
                                           {chat_ids[1], {"anna"}}};
  std::vector<entities::Chat> res =
      use_case::GetChatListUC(mock_get_session_login, mock_getter_chat_list,
                              mock_get_user_list)
          .Execute(token);
  EXPECT_EQ(res, chats);
}

/**
 * @brief Тест добавления в датасет
 *
 */
TEST(AddToDatasetUC, SuccessAddToDataset) {
  // Запрос со существующей сессии
  auto token = std::string("token");
  auto login = std::string("login");
  auto mock_get_session_login = std::make_shared<MockIGetSessionLogin const>();
  EXPECT_CALL(*mock_get_session_login, GetSessionLogin(token))
      .WillOnce(Return(login));
  // Отправляем в датасет
  auto data = "qwerty";
  auto label = true;
  auto mock_add_dataset = std::make_shared<MockIAdditionalDataset const>();
  EXPECT_CALL(*mock_add_dataset, AdditionalDataset(data, label)).Times(1);

  // Запускаем сценарий
  use_case::AddToDatasetUC(mock_get_session_login, mock_add_dataset)
      .Execute(token, data, label);
}

}  // namespace calmgram::api_server::tests