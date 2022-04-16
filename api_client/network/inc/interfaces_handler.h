#ifndef API_CLIENT_INTERFACES_HANDLER_H
#define API_CLIENT_INTERFACES_HANDLER_H

#include "structs.h"

namespace calmgram::api_client::network {

    class IHandler {
    public:
        virtual bool Execute() = 0;
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_INTERFACES_HANDLER_H
