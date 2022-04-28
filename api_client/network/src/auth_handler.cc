#include "auth_handler.h"

namespace calmgram::api_client::network {

    bool AuthorisationHandler::Execute(int id) {
        if (id >= 0)
            return true;
        return false;
    }

}
