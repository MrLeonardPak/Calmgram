#include "core.h"
#include "add_chat_converter.h"

int main () {
    calmgram::api_client::core::Core core;
    core.run();
    // calmgram::api_client::converters::AddChatConverter adchconv;
    // int ids[]={1, 2};
    // adchconv.DataToRequest(ids,2);
    return 1;
}