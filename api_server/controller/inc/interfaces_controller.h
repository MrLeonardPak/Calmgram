#ifndef CALMGRAM_API_SERVER_INTERFACES_CONTROLLER_H
#define CALMGRAM_API_SERVER_INTERFACES_CONTROLLER_H

#include "entities.h"

#include <any>
#include <concepts>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace calmgram::api_server::controller {

// Концепт для внешней зависимости - парсер
template <typename T>
concept Refreshable = requires(T t) {
  t.Refresh();
};

template <typename T>
concept GetValueTemplatable = requires(T t, std::string str) {
  { t.template GetValue<int>(str) } -> std::same_as<int>;
};

template <typename T>
concept GetVectorTemplatable = requires(T t, std::string str) {
  { t.template GetVector<int>(str) } -> std::same_as<std::vector<int>>;
};

template <typename T>
concept GetStringEnable = requires(T t) {
  { t.GetString() } -> std::same_as<std::string>;
};

template <typename T>
concept SetValueTemplatable = requires(T t, std::string str, int val_int) {
  t.template SetValue(str, val_int);
};

template <typename T>
concept SetVectorTemplatable =
    requires(T t,
             std::string str,
             std::vector<int> vect_int,
             std::vector<entities::Message> vect_msg) {
  t.template SetVector(str, vect_int);
  t.template SetVector(str, vect_msg);
};

template <typename T>
concept parser_class = std::constructible_from<T, std::string> &&
    GetValueTemplatable<T> && Refreshable<T> && SetVectorTemplatable<T> &&
    GetStringEnable<T> && SetValueTemplatable<T> && GetVectorTemplatable<T>;

class Response {
 public:
  enum Status { OK, NOT_PAGE, ERROR_DATA, WRONG_TYPE };

  Response(Status status, std::string&& body) : status_(status), body_(body){};
  ~Response() = default;

  Status get_status() const { return status_; }
  std::string get_body() const { return body_; }

 private:
  Status status_;
  std::string body_;
};

class IRequest {
 public:
  enum RequestType { GET, POST };

  virtual ~IRequest() = default;
  virtual std::string get_path() const = 0;
  virtual RequestType get_type() const = 0;
  virtual std::string get_body() const = 0;
};

class IHandler {
 public:
  virtual ~IHandler() = default;
  virtual Response Handle(IRequest const& request) = 0;
};

namespace body_fields {

auto constexpr kToken = "token";
auto constexpr kLogin = "login";
auto constexpr kPassword = "password";
auto constexpr kChatId = "chat_id";
auto constexpr kFromTime = "from_time";
auto constexpr kText = "text";
auto constexpr kUserLogins = "user_logins";
auto constexpr kChatIds = "chat_ids";
auto constexpr kMsgs = "msgs";

}  // namespace body_fields

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_INTERFACES_CONTROLLER_H