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

        virtual bool Execute(int chat_id, time_t last_update, std::string const& token) = 0;
        virtual std::vector<entities::Message> GetData() = 0;
    };

    class ISendMessage {
    public:
        virtual ~ISendMessage() = default;

        virtual bool Execute(int chat_id, entities::Content content, std::string const& token) = 0;
    };

    class IAddChat {
    public:
        virtual ~IAddChat() = default;

        virtual bool Execute(std::vector<std::string> const& target_logins, std::string const& token) = 0;
    };

    class IAuthorisation {
    public:
        virtual ~IAuthorisation() = default;
        
        virtual bool Execute(std::string const& login, std::string const& password) = 0;
        virtual std::string GetData() = 0;
    };

    class IReportAboutMark {
    public:
        virtual ~IReportAboutMark() = default;

        virtual bool Execute(std::string msg, bool is_marked, std::string const& token) = 0;
    };

    class IUpdateChats {
    public:
        virtual ~IUpdateChats() = default;

        virtual bool Execute(std::string const& token) = 0;
        virtual std::vector<entities::EmptyChat> GetData() = 0;
    };

} // namespace calmgram::api_client::network


#endif //API_CLIENT_INTERFACES_HANDLERS_H
