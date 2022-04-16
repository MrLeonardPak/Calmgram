#ifndef API_CLIENT_AUTH_HANDLER_H
#define API_CLIENT_AUTH_HANDLER_H

#include "auth_converter.h"
#include "interfaces_handlers.h"

namespace calmgram::api_client::network {

    class AuthorisationHandler : public IAuthorisation {
    private:
        int id_;
        converters::AuthorisationConverter converter_;
        std::vector<int> output;
    public:
        AuthorisationHandler() = default;
        ~AuthorisationHandler() = default;

        bool Execute(int id) override;
        std::vector<int> GetData() override {return output; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_AUTH_HANDLER_H
