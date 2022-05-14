#ifndef API_CLIENT_ADD_CHAT_HANDLER_H
#define API_CLIENT_ADD_CHAT_HANDLER_H

#include "interfaces_handlers.h"


#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::network {

    class AddChatHandler : public IAddChat {
    private:
        std::string request_;
        int output_;
        
    public:
        AddChatHandler() = default;
        ~AddChatHandler() = default;

        bool Execute(int id_1, int id_2) override;

        bool DataToRequest(int* ids, int n);
        bool ResponseToData(std::string response);

        int GetData() override { return output_; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_ADD_CHAT_HANDLER_H
