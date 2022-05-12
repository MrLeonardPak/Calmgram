#include "core.h"

int main (int argc, char *argv[]) {
    calmgram::api_client::core::Core core;
    // return core.run(argc, argv);
    core.consol_run();
    return 1;
}