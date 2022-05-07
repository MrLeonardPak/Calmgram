#include "controller_test.h"
// #include "json_parser.hpp"
#include "user_auth_handler.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;
using ::testing::Truly;

namespace calmgram::api_server::tests {

TEST(UserAuthHandler, OkResponse) {
  // Ничего не ожидаем от интерфейсов на уровне UseCase
  auto mock_get_user = std::make_shared<MockIGetUser>();
  EXPECT_CALL(*mock_get_user, GetUser(_)).WillOnce(Return(entities::User{}));
  auto mock_create_user = std::make_shared<MockICreateUser>();
  EXPECT_CALL(*mock_create_user, CreateUser(_)).Times(0);
  // Фиксируем вызовы интерфейса Request
  auto user_auth = use_case::UserAuthUC(mock_get_user, mock_create_user);
  MockRequest mock_request;
  EXPECT_CALL(mock_request, get_type())
      .WillRepeatedly(Return(controller::Request::POST));
  EXPECT_CALL(mock_request, get_body()).WillRepeatedly(Return("{}"));
  // Вызываем обработчик
  controller::Response response =
      controller::UserAuthHandler<MockParser>(user_auth).Handle(mock_request);
  // Ожидаем, что быдет ответ об успехе
  EXPECT_EQ(response.get_status(), controller::Response::OK);
}

}  // namespace calmgram::api_server::tests