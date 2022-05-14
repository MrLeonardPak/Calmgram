#include "send_msg_handler.h"

#include <iostream>

namespace calmgram::api_client::network {

    bool SendMessageHandler::Execute(int chat_id, int user_id, entities::Content content) {
        if (!DataToRequest(chat_id,user_id,content)) {
            return false;
        }
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request_, "/chat/send", false);
        if (response == "Error") {
            return false;
        }
        return true;
    }

    bool SendMessageHandler::DataToRequest(int chat_id,
                                            int user_id,
                                            entities::Content content) {
    try {
        boost::property_tree::ptree tree;
        tree.put("chat_id", chat_id);
        tree.put("user_id", user_id);
        tree.put("text", content.data);
        std::ostringstream buf;
        write_json(buf, tree, false);
        std::string json = buf.str();

        request_ = json;
    } catch (std::exception const& e) {
        std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
        return false;
    }
    return true;
    }

}

