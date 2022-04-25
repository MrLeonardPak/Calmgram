#ifndef CALMGRAM_API_SERVER_ENTITY_H
#define CALMGRAM_API_SERVER_ENTITY_H

#include <string>
#include <tuple>
#include <vector>

namespace calmgram::api_server::entities {

enum TypeOfContent { TEXT, JPEG };

struct Content {
  std::string data;
  TypeOfContent type;

  friend bool operator==(Content const& l, Content const& r) {
    return std::tie(l.data, l.type) == std::tie(r.data, r.type);
  }
};

struct Message {
  int owner_id;
  time_t created;
  Content content;
  bool is_marked;

  friend bool operator==(Message const& l, Message const& r) {
    return std::tie(l.owner_id, l.created, l.content, l.is_marked) ==
           std::tie(r.owner_id, r.created, r.content, r.is_marked);
  }
};

struct Chat {
  int id;
  std::vector<Message> msgs;
};

struct User {
  int id;
  std::vector<Chat> chats;
};

}  // namespace calmgram::api_server::entities

#endif  // CALMGRAM_API_SERVER_ENTITY_H