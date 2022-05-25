#ifndef API_CLIENT_AUTH_HANDLER_H
#define API_CLIENT_AUTH_HANDLER_H

#include "interfaces_handlers.h"

namespace calmgram::api_client::network {

    class AuthorisationHandler : public IAuthorisation {
    private:
        std::string request_;
        std::string output_;
    public:
        AuthorisationHandler() = default;
        ~AuthorisationHandler() = default;

        bool Execute(std::string const& login, std::string const& password) override;
        
        bool DataToRequest(std::string const& login, std::string const& password);
        bool ResponseToData(std::string response);
        
        std::string GetData() override {return output_; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_AUTH_HANDLER_H
