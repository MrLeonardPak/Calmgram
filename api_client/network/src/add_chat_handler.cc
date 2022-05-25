#include "add_chat_handler.h"

#include <iostream>

namespace calmgram::api_client::network {

    bool AddChatHandler::Execute(std::vector<std::string> const& target_logins, std::string const& token) {
        
        if (!DataToRequest(target_logins, token)) {
            return false;
        }
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request_, "/chat/add",false);
        if (response == "Error") {
            return false;
        }
        return true;
    }

    bool AddChatHandler::DataToRequest(std::vector<std::string> const& target_logins, std::string const& token) {
        try {
            boost::property_tree::ptree tree;
            tree.put("token", token);
            // массив
            boost::property_tree::ptree child;
            boost::property_tree::ptree children;
            for (std::string login : target_logins) {
                child.put("", login);
                children.push_back(std::make_pair("", child));    
            }
            tree.add_child("logins", children);
            
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
