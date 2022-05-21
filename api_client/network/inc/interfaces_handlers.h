#ifndef API_CLIENT_INTERFACES_HANDLERS_H
#define API_CLIENT_INTERFACES_HANDLERS_H

#include "entities.h"
#include "request_sender.h"

#include <ctime>
#include <vector>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::network {

    class IUpdateChat {
    public:
        virtual ~IUpdateChat() = default;

        virtual bool Execute(int user_id, int chat_id, time_t last_update) = 0;
        virtual std::vector<entities::Message> GetData() = 0;
    };

    class ISendMessage {
    public:
        virtual ~ISendMessage() = default;

        virtual bool Execute(int chat_id, int user_id, entities::Content content) = 0;
    };

    class IAddChat {
    public:
        virtual ~IAddChat() = default;

        virtual bool Execute(std::vector<int> ids) = 0;
        virtual int GetData() = 0;
    };

    class IAuthorisation {
    public:
        virtual ~IAuthorisation() = default;
        
        virtual bool Execute(int id) = 0;
        virtual std::vector<int> GetData() = 0;
    };

    class IReportAboutMark {
    public:
        virtual ~IReportAboutMark() = default;

        virtual bool Execute(std::string msg, bool is_marked) = 0;
    };

} // namespace calmgram::api_client::network


#endif //API_CLIENT_INTERFACES_HANDLERS_H
