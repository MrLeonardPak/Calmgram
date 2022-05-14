#include "add_chat_handler.h"

#include <iostream>

namespace calmgram::api_client::network {

    bool AddChatHandler::Execute(std::vector<int> ids) {
        
        if (!DataToRequest(ids)) {
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

    bool AddChatHandler::DataToRequest(std::vector<int> ids) {  // добавить обработку ошибок
        try {
            boost::property_tree::ptree tree;
            // массив
            boost::property_tree::ptree child;
            boost::property_tree::ptree children;
            for (int id : ids) {
                child.put("",id);
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
