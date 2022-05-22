#include <iostream>
#include <cstring>

#include "core.h"

int main (int argc, char *argv[]) {
    calmgram::api_client::client_core::Core core;
    core.run(argc, argv);
    return 0;
}
