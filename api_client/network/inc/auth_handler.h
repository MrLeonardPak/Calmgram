#ifndef API_CLIENT_AUTH_HANDLER_H
#define API_CLIENT_AUTH_HANDLER_H

#include "interfaces_handlers.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::network {

    class AuthorisationHandler : public IAuthorisation {
    private:
        std::string request_;
        std::vector<int> output_;
    public:
        AuthorisationHandler() = default;
        ~AuthorisationHandler() = default;

        bool Execute(int id) override;
        
        bool DataToRequest(int id);
        bool ResponseToData(std::string response);
        
        std::vector<int> GetData() override {return output_; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_AUTH_HANDLER_H
