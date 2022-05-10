#include "controller_test.h"
// #include "json_parser.hpp"
#include "user_auth_handler.hpp"

using ::testing::_;
using ::testing::Mock;
using ::testing::Return;
using ::testing::Throw;
using ::testing::Truly;

namespace calmgram::api_server::tests {

TEST(UserAuthHandler, OkResponse) {
  auto mock_user_auth_uc = std::make_unique<MockUserAuthUC>();
  std::vector<int> chats{123};
  EXPECT_CALL(*mock_user_auth_uc, Execute(_)).WillOnce(Return(chats));
  // Фиксируем вызовы интерфейса Request
  MockRequest mock_request;
  EXPECT_CALL(mock_request, get_type())
      .WillRepeatedly(Return(controller::IRequest::POST));
  EXPECT_CALL(mock_request, get_body()).WillRepeatedly(Return("{}"));
  // Вызываем обработчик
  controller::Response response =
      controller::UserAuthHandler<MockParser>(std::move(mock_user_auth_uc))
          .Handle(mock_request);
  // Ожидаем, что быдет ответ об успехе
  EXPECT_EQ(response.get_status(), controller::Response::OK);
}

}  // namespace calmgram::api_server::tests