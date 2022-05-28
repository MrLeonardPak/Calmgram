#include "controller_test.h"
#include "add_chat_handler.hpp"
#include "add_to_dataset_handler.hpp"
#include "get_chat_list_handler.hpp"
#include "send_msg_handler.hpp"
#include "update_chat_handler.hpp"
#include "user_auth_handler.hpp"

using ::testing::_;
using ::testing::Mock;
using ::testing::Return;
using ::testing::Throw;
using ::testing::Truly;

namespace calmgram::api_server::tests {

TEST(UserAuthHandler, OkResponse) {
  auto mock_user_auth_uc = std::make_unique<MockUserAuthUC>();
  auto token = "token";
  EXPECT_CALL(*mock_user_auth_uc, Execute(_, _)).WillOnce(Return(token));
  // Фиксируем вызовы интерфейса Request
  MockRequest mock_request;
  EXPECT_CALL(mock_request, get_type())
      .WillRepeatedly(Return(controller::IRequest::CONNECT));
  EXPECT_CALL(mock_request, get_body()).WillRepeatedly(Return("{}"));
  // Вызываем обработчик
  controller::Response response =
      controller::UserAuthHandler<MockParser>(std::move(mock_user_auth_uc))
          .Handle(mock_request);
  // Ожидаем, что быдет ответ об успехе
  EXPECT_EQ(response.get_status(), controller::Response::OK);
}

TEST(UpdateChatHandler, OkResponse) {
  auto mock_update_chat_uc = std::make_unique<MockUpdateChatUC>();
  std::vector<entities::Message> msgs(1);
  EXPECT_CALL(*mock_update_chat_uc, Execute(_, _, _)).WillOnce(Return(msgs));
  // Фиксируем вызовы интерфейса Request
  MockRequest mock_request;
  EXPECT_CALL(mock_request, get_type())
      .WillRepeatedly(Return(controller::IRequest::GET));
  EXPECT_CALL(mock_request, get_body()).WillRepeatedly(Return("{}"));
  // Вызываем обработчик
  controller::Response response =
      controller::UpdateChatHandler<MockParser>(std::move(mock_update_chat_uc))
          .Handle(mock_request);
  // Ожидаем, что быдет ответ об успехе
  EXPECT_EQ(response.get_status(), controller::Response::OK);
}

TEST(SendMsgHandler, OkResponse) {
  auto mock_send_msg_uc = std::make_unique<MockSendMsgUC>();
  EXPECT_CALL(*mock_send_msg_uc, Execute(_, _, _)).Times(1);
  // Фиксируем вызовы интерфейса Request
  MockRequest mock_request;
  EXPECT_CALL(mock_request, get_type())
      .WillRepeatedly(Return(controller::IRequest::POST));
  EXPECT_CALL(mock_request, get_body()).WillRepeatedly(Return("{}"));
  // Вызываем обработчик
  controller::Response response =
      controller::SendMsgHandler<MockParser>(std::move(mock_send_msg_uc))
          .Handle(mock_request);
  // Ожидаем, что быдет ответ об успехе
  EXPECT_EQ(response.get_status(), controller::Response::OK);
}

TEST(AddChatHandler, OkResponse) {
  auto mock_add_chat_uc = std::make_unique<MockAddChatUC>();
  EXPECT_CALL(*mock_add_chat_uc, Execute(_, _)).WillOnce(Return(123));
  // Фиксируем вызовы интерфейса Request
  MockRequest mock_request;
  EXPECT_CALL(mock_request, get_type())
      .WillRepeatedly(Return(controller::IRequest::POST));
  EXPECT_CALL(mock_request, get_body()).WillRepeatedly(Return("{}"));
  // Вызываем обработчик
  controller::Response response =
      controller::AddChatHandler<MockParser>(std::move(mock_add_chat_uc))
          .Handle(mock_request);
  // Ожидаем, что быдет ответ об успехе
  EXPECT_EQ(response.get_status(), controller::Response::OK);
}

TEST(GetChatListHandler, OkResponse) {
  auto chats = std::vector<entities::Chat>{{1, {"anna"}}, {1, {"anna"}}};
  auto mock_get_chat_uc = std::make_unique<MockGetChatListUC>();
  EXPECT_CALL(*mock_get_chat_uc, Execute(_)).WillOnce(Return(chats));
  // Фиксируем вызовы интерфейса Request
  MockRequest mock_request;
  EXPECT_CALL(mock_request, get_type())
      .WillRepeatedly(Return(controller::IRequest::GET));
  EXPECT_CALL(mock_request, get_body()).WillRepeatedly(Return("{}"));
  // Вызываем обработчик
  controller::Response response =
      controller::GetChatListHandler<MockParser>(std::move(mock_get_chat_uc))
          .Handle(mock_request);
  // Ожидаем, что быдет ответ об успехе
  EXPECT_EQ(response.get_status(), controller::Response::OK);
}

TEST(AddToDatasetHandler, OkResponse) {
  auto chats = std::vector<entities::Chat>{{1, {"anna"}}, {1, {"anna"}}};
  auto mock_add_to_dataset_uc = std::make_unique<MockAddToDatasetUC>();
  EXPECT_CALL(*mock_add_to_dataset_uc, Execute(_, _, _)).Times((1));
  // Фиксируем вызовы интерфейса Request
  MockRequest mock_request;
  EXPECT_CALL(mock_request, get_type())
      .WillRepeatedly(Return(controller::IRequest::POST));
  EXPECT_CALL(mock_request, get_body()).WillRepeatedly(Return("{}"));
  // Вызываем обработчик
  controller::Response response = controller::AddToDatasetHandler<MockParser>(
                                      std::move(mock_add_to_dataset_uc))
                                      .Handle(mock_request);
  // Ожидаем, что быдет ответ об успехе
  EXPECT_EQ(response.get_status(), controller::Response::OK);
}

}  // namespace calmgram::api_server::tests