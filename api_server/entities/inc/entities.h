#ifndef CALMGRAM_API_SERVER_ENTITY_H
#define CALMGRAM_API_SERVER_ENTITY_H

#include <string>
#include <vector>

namespace calmgram::api_server::entities {

enum TypeOfContent { TEXT, JPEG };

struct Content {
  std::string data;
  TypeOfContent type;
};

struct Message {
  int owner_id;
  time_t created;
  Content content;
  bool is_marked;
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