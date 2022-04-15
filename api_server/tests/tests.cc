/**
 * lcov -t "tests/tests_kmeans" -o coverage.info -c -d kmeans_libs/
 * genhtml -o report coverage.info
 * cd report && python3 -m http.server 8000
 */
#include "gtest/gtest.h"
#include "user_auth_handler.h"

TEST(Test_test, testing) {
  namespace router = ::calmgram::api_server::router;
  router::UserAuthHandler handler;
  router::Request request;
  EXPECT_TRUE(handler.ShouldExecute(request));
}