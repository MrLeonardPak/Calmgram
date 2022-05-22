#include <iostream>
#include <cstring>

#include "core.h"

int main (int argc, char *argv[]) {
    if ( argc > 1) {
        calmgram::api_client::client_core::Core core;
        core.run(argc, argv);
    } else {
        std::cout << "no args, pls add -console or -window" << std::endl;
    }
    return 0;
}
