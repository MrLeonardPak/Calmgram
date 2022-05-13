#ifndef CALMGRAM_API_SERVER_CONTROLLER_TEST_H
#define CALMGRAM_API_SERVER_CONTROLLER_TEST_H

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "interfaces_controller.h"
#include "interfaces_uc_input.h"

namespace calmgram::api_server::tests {

namespace impl {

using StructureType = std::unordered_map<std::string, std::any>;

}  // namespace impl

class MockUserAuthUC : public use_case::IUserAuthUC {
 public:
  MOCK_METHOD(std::vector<int>, Execute, (int user_id), (override));
};

class MockUpdateChatUC : public use_case::IUpdateChatUC {
 public:
  MOCK_METHOD(std::vector<entities::Message>,
              Execute,
              (int user_id, int chat_id, time_t from_time),
              (override));
};

class MockSendMsgUC : public use_case::ISendMsgUC {
 public:
  MOCK_METHOD(void,
              Execute,
              (int user_id, int chat_id, entities::Content const& content),
              (override));
};

class MockAddChatUC : public use_case::IAddChatUC {
 public:
  MOCK_METHOD(int, Execute, (std::vector<int> users), (override));
};

class MockRequest : public controller::IRequest {
 public:
  MOCK_METHOD(std::string, get_path, (), (const, override));
  MOCK_METHOD(RequestType, get_type, (), (const, override));
  MOCK_METHOD(std::string, get_body, (), (const, override));
};

class MockParser {
 public:
  MockParser(std::string const& str) {}

  void Refresh(){};

  template <typename T>
  T GetValue(std::string const& name) {
    return T();
  }

  template <typename T>
  std::vector<T> GetVector(std::string const& name) {
    return std::vector<T>();
  }

  std::string GetString() { return {}; }

  template <typename T>
  void SetValue(std::string const& name, T const& value) {}

  template <typename T>
  void SetVector(std::string const& name, std::vector<T> const& vector);
};

template <typename T>
void MockParser::SetVector(std::string const& name,
                           std::vector<T> const& vector) {}

template <>
void MockParser::SetVector<entities::Message>(
    std::string const& name,
    std::vector<entities::Message> const& vector) {}

}  // namespace calmgram::api_server::tests

#endif  // CALMGRAM_API_SERVER_CONTROLLER_TEST_H