#ifndef CALMGRAM_API_SERVER_ENTITY_H
#define CALMGRAM_API_SERVER_ENTITY_H

#include <string>
#include <vector>

namespace calmgram::api_server::entities {

enum TypeOfContent { TEXT, JPEG };

struct Content {
  std::string data;
  TypeOfContent type;

  Content() = default;
};

struct Message {
  int owner_id;
  time_t created;
  Content content;
  bool is_marked;

  Message() = default;
};

struct Chat {
  int id;
  std::vector<Message> msgs;

  Chat(int id, std::vector<Message> msgs) : id(id), msgs(msgs) {}
  Chat(int id) : id(id), msgs(std::vector<Message>()) {}
};

struct User {
  int id;
  std::vector<Chat> chats;

  User() = default;
  User(int id, std::vector<Chat> chats) : id(id), chats(chats) {}
  User(int id) : id(id), chats(std::vector<Chat>()) {}
};

}  // namespace calmgram::api_server::entities

#endif  // CALMGRAM_API_SERVER_ENTITY_H