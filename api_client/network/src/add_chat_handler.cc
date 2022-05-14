#include "add_chat_handler.h"

#include <iostream>

namespace calmgram::api_client::network {

    bool AddChatHandler::Execute(int id_1, int id_2) {
        int ids[]={id_1, id_2};
        if (!DataToRequest(ids,2)) {
            return false;
        }
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request_, "/chat/add",false);
        if (response == "Error") {
            return false;
        }
        if (!ResponseToData(response)) {
            return false;
        }
        return true;
    }

    bool AddChatHandler::DataToRequest(int* ids,
                                        int n) {  // добавить обработку ошибок
        try {
            boost::property_tree::ptree tree;
            // массив
            boost::property_tree::ptree child;
            boost::property_tree::ptree children;
            for (int i = 0; i < n; i++) {
            child.put("",ids[i]);
            children.push_back(std::make_pair("", child));

            }
            tree.add_child("user_ids", children);
            
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

    bool AddChatHandler::ResponseToData(std::string response) {

        try {
            std::stringstream buff;
            buff << response;
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(buff, tree);
            output_ = tree.get<int>("chat_id");
        } catch (std::exception const& e) {
            std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
            return false;
        }
        return true;
    }
}
