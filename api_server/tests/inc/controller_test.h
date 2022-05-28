#ifndef CALMGRAM_API_SERVER_CONTROLLER_TEST_H
#define CALMGRAM_API_SERVER_CONTROLLER_TEST_H

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "interfaces_controller.h"
#include "interfaces_uc_input.h"

#include <boost/core/ignore_unused.hpp>

namespace calmgram::api_server::tests {

namespace impl {

using StructureType = std::unordered_map<std::string, std::any>;

}  // namespace impl

class MockUserAuthUC : public use_case::IUserAuthUC {
 public:
  MOCK_METHOD(std::string,
              Execute,
              (std::string_view login, std::string_view password),
              (override));
};

class MockUpdateChatUC : public use_case::IUpdateChatUC {
 public:
  MOCK_METHOD(std::vector<entities::Message>,
              Execute,
              (std::string_view token, int chat_id, time_t from_time),
              (override));
};

class MockSendMsgUC : public use_case::ISendMsgUC {
 public:
  MOCK_METHOD(void,
              Execute,
              (std::string_view token,
               int chat_id,
               entities::Content const& content),
              (override));
};

class MockAddChatUC : public use_case::IAddChatUC {
 public:
  MOCK_METHOD(int,
              Execute,
              (std::string_view token,
               std::vector<std::string_view> const& user_logins),
              (override));
};

class MockAddToDatasetUC : public use_case::IAddToDatasetUC {
 public:
  MOCK_METHOD(void,
              Execute,
              (std::string_view token, std::string_view data, bool label),
              (override));
};

class MockGetChatListUC : public use_case::IGetChatListUC {
 public:
  MOCK_METHOD(std::vector<entities::Chat>,
              Execute,
              (std::string_view token),
              (override));
};

class MockRequest : public controller::IRequest {
 public:
  MOCK_METHOD(std::string, get_path, (), (const, override));
  MOCK_METHOD(RequestType, get_type, (), (const, override));
  MOCK_METHOD(std::string, get_body, (), (const, override));
};

class MockParser {
 public:
  MockParser(std::string const& str) { ::boost::ignore_unused(str); }

  void Refresh(){};

  template <typename T>
  T GetValue(std::string const& name) {
    ::boost::ignore_unused(name);
    return T();
  }

  template <typename T>
  std::vector<T> GetVector(std::string const& name) {
    ::boost::ignore_unused(name);
    return std::vector<T>();
  }

  std::string GetString() { return {}; }

  template <typename T>
  void SetValue(std::string const& name, T const& value) {
    ::boost::ignore_unused(name);
    ::boost::ignore_unused(value);
  }

  template <typename T>
  void SetVector(std::string const& name, std::vector<T> const& vector);
};

template <typename T>
void MockParser::SetVector(std::string const& name,
                           std::vector<T> const& vector) {
  ::boost::ignore_unused(name);
  ::boost::ignore_unused(vector);
}

template <>
void MockParser::SetVector<entities::Message>(
    std::string const& name,
    std::vector<entities::Message> const& vector) {
  ::boost::ignore_unused(name);
  ::boost::ignore_unused(vector);
}

template <>
void MockParser::SetVector<entities::Chat>(
    std::string const& name,
    std::vector<entities::Chat> const& vector) {
  ::boost::ignore_unused(name);
  ::boost::ignore_unused(vector);
}

}  // namespace calmgram::api_server::tests

#endif  // CALMGRAM_API_SERVER_CONTROLLER_TEST_H