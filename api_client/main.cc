#include "core.h"

int main (int argc, char *argv[]) {
    calmgram::api_client::core::Core core;
    // return core.run(argc, argv);
    core.consol_run();
    
    //  временно чтобы компилятор не ругался
    if (argv[argc - 1][0] == '0') {
        return 0;
    }
    return 1;
}