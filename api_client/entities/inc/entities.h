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
        std::string sender;
        bool is_marked;
        time_t time;
        Content content;
    };

    struct Chat {
        int id;
        bool is_updated;
        std::vector<std::string> companions;
        std::vector<Message> messages;
    };

    struct Profile {
        std::string login;
        std::string password;
        std::string token;
        std::vector<Chat> chats;
    };
    

    struct EmptyChat {
        int id;
        bool is_updated;
        std::vector<std::string> companions;
    };
}  // namespace calmgram::api_client::entities

#endif  // CALMGRAM_API_CLIENT_ENTITIES_H
