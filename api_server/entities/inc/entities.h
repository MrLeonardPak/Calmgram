#ifndef CALMGRAM_API_SERVER_ENTITY_H
#define CALMGRAM_API_SERVER_ENTITY_H

#include <array>
#include <string>
#include <tuple>
#include <vector>

namespace calmgram::api_server::entities {

// Структура осталась для будущей передаче вместе с текстом изображений
struct Content {
  std::string text;

  friend bool operator==(Content const& l, Content const& r) {
    return std::tie(l.text) == std::tie(r.text);
  }
};

struct Message {
  std::string owner_login;
  time_t created;
  Content content;
  bool is_marked;

  friend bool operator==(Message const& l, Message const& r) {
    return std::tie(l.owner_login, l.created, l.content, l.is_marked) ==
           std::tie(r.owner_login, r.created, r.content, r.is_marked);
  }
};

struct Chat {
  int id;
  std::vector<std::string> user_logins;

  friend bool operator==(Chat const& l, Chat const& r) {
    return std::tie(l.id, l.user_logins) == std::tie(r.id, r.user_logins);
  }
};

struct User {
  std::string login;
  std::vector<int> chats;

  friend bool operator==(User const& l, User const& r) {
    return std::tie(l.login, l.chats) == std::tie(r.login, r.chats);
  }
};

}  // namespace calmgram::api_server::entities

#endif  // CALMGRAM_API_SERVER_ENTITY_H