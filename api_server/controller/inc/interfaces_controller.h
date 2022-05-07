#ifndef CALMGRAM_API_SERVER_INTERFACES_CONTROLLER_H
#define CALMGRAM_API_SERVER_INTERFACES_CONTROLLER_H

#include <any>
#include <concepts>
#include <memory>
#include <string>
#include <unordered_map>

#include <iostream>

namespace calmgram::api_server::controller {

// Концепт для внешней зависимости - парсер
template <typename T>
concept parser_class = std::constructible_from<T, std::string> &&
    requires(T t, std::string str) {
  { t.template GetValue<int>(str) } -> std::same_as<int>;
  { t.template GetValue<char>(str) } -> std::same_as<char>;
};

class Response {
 public:
  enum Status { OK, NOT_PAGE, ERROR_DATA, WRONG_TYPE };

  Response(Status status, std::unordered_map<std::string, std::any>&& body)
      : status_(status), body_(body){};
  ~Response() = default;

  Status get_status() const { return status_; }

 private:
  Status status_;
  std::unordered_map<std::string, std::any> body_;
};

class Request {
 public:
  enum RequestType { GET, POST };

  virtual ~Request() = default;
  virtual std::string get_path() const = 0;
  virtual RequestType get_type() const = 0;
  virtual std::string get_body() const = 0;
};

class IHandler {
 public:
  virtual ~IHandler() = default;
  virtual Response Handle(Request const& request) = 0;
};

namespace constants {

auto constexpr kUserId = "user_id";
auto constexpr kChatId = "chat_id";
auto constexpr kFromTime = "from_time";
auto constexpr kContetType = "content_type";
auto constexpr kText = "text";
auto constexpr kImage = "image";
auto constexpr kUsers = "users";
auto constexpr kChats = "chats";

}  // namespace constants

}  // namespace calmgram::api_server::controller

#endif  // CALMGRAM_API_SERVER_INTERFACES_CONTROLLER_H