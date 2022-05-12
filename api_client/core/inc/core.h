#ifndef CALMGRAM_API_CLIENT_CORE_H
#define CALMGRAM_API_CLIENT_CORE_H
#pragma once

#include "user_uc.h"

namespace calmgram::api_client::core {
    
    
    class Core {
    private: 
    
    public:
        int run(int argc, char *argv[]);
        void consol_run();

    };



}  // namespace calmgram::api_client::core

#endif  // CALMGRAM_API_CLIENT_CORE_H