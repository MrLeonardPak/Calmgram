#ifndef API_CLIENT_INTERFACES_HANDLERS_H
#define API_CLIENT_INTERFACES_HANDLERS_H

#include "structs.h"
#include "entities.h"

#include <ctime>
#include <vector>

namespace calmgram::api_client::network {

    class IUpdateChat {
    public:
        virtual bool Execute(int chat_id, time_t last_update) = 0;
        virtual std::vector<entities::Message> GetData() = 0;
    };

    class ISendMessage {
    public:
        virtual bool Execute(int chat_id, int user_id, entities::Content content) = 0;
        virtual bool GetData() = 0;
    };

    class IAddChat {
    public:
        virtual bool Execute(int id_1, int id_2) = 0;
        virtual int GetData() = 0;
    };

    class IAuthorisation {
    public:
        virtual bool Execute(int id) = 0;
        virtual std::vector<int> GetData() = 0;
    };

} // namespace calmgram::api_client::network


#endif //API_CLIENT_INTERFACES_HANDLERS_H
