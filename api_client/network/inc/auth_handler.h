#ifndef API_CLIENT_AUTH_HANDLER_H
#define API_CLIENT_AUTH_HANDLER_H

#include "auth_converter.h"

#include <vector>

namespace calmgram::api_client::network {

    class AuthorisationHandler {
    private:
        int id_;
        converters::AuthorisationConverter converter_;
        std::vector<int> output;
    public:
        AuthorisationHandler(int id)
            : id_(id) {}
        ~AuthorisationHandler() = default;

        bool Execute();
        std::vector<int> GetData() {return output; }
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_AUTH_HANDLER_H
