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
  std::string_view owner_login;
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
  std::vector<Message> msgs;
};

struct User {
  int id;
  std::vector<int> chats;
};

}  // namespace calmgram::api_server::entities

#endif  // CALMGRAM_API_SERVER_ENTITY_H