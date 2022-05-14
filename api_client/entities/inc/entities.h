#ifndef CALMGRAM_API_CLIENT_ENTITIES_H
#define CALMGRAM_API_CLIENT_ENTITIES_H
#pragma once

#include <string>
#include <vector>
#include <ctime>

namespace calmgram::api_client::entities {
    enum TypeOfContent { TEXT };

    struct Content {
        std::string data;
        TypeOfContent type; // сейчас только текст, в дальнейшем могут быть изображения, ответы и прочее
    };

    struct Message {
        int owner_id;
        bool is_marked;
        time_t time;
        Content content;
    };

    struct Chat {
        int id;
        std::vector<Message> messages;
    };

    struct Profile {
        int id;
        std::vector<Chat> chats;
        time_t last_update;
    };

}  // namespace calmgram::api_client::entities

#endif  // CALMGRAM_API_CLIENT_ENTITIES_H