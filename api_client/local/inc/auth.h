#ifndef API_CLIENT_AUTH_H
#define API_CLIENT_AUTH_H

#include "interfaces_handlers.h"

#include <iostream>

namespace calmgram::api_client::local {

    class AuthorisationHandler : public network::IAuthorisation {
    private:
        std::string output_;
    public:
        AuthorisationHandler() = default;
        ~AuthorisationHandler() = default;

        bool Execute(std::string const& login, std::string const& password) override {
            std::cout << "login: " << login << " password: " << password << std::endl;
            output_ = "asdfg";
            return true;
        }
        
        std::string GetData() override {return output_; }
    };

} // namespace calmgram::api_client::local

#endif //API_CLIENT_AUTH_H
