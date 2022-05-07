#ifndef CALMGRAM_API_SERVER_CONTROLLER_TEST_H
#define CALMGRAM_API_SERVER_CONTROLLER_TEST_H

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "interfaces_controller.h"
#include "use_case_test.h"

namespace calmgram::api_server::tests {

namespace controller = ::calmgram::api_server::controller;

class MockRequest : public controller::Request {
 public:
  MOCK_METHOD(std::string, get_path, (), (const, override));
  MOCK_METHOD(RequestType, get_type, (), (const, override));
  MOCK_METHOD(std::string, get_body, (), (const, override));
};

class MockParser {
 public:
  MockParser(std::string str) {}

  template <typename T>
  T GetValue(std::string name) {
    return T();
  }
};

}  // namespace calmgram::api_server::tests

#endif  // CALMGRAM_API_SERVER_CONTROLLER_TEST_H