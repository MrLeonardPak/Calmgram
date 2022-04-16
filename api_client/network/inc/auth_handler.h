#ifndef API_CLIENT_AUTH_HANDLER_H
#define API_CLIENT_AUTH_HANDLER_H

#include "auth_converter.h"
#include "interfaces_handler.h"

#include <vector>

namespace calmgram::api_client::network {

    class AuthorisationHandler : public IHandler{
    private:
        int id_;
        converters::AuthorisationConverter converter_;
        std::vector<int> output;
    public:
        AuthorisationHandler(int id)
            : id_(id) {}
        ~AuthorisationHandler() = default;

        bool Execute() override;
        std::vector<int> GetData() {return output; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_AUTH_HANDLER_H
