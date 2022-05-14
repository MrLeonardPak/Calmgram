#include "auth_handler.h"

#include <iostream>

namespace calmgram::api_client::network {

    bool AuthorisationHandler::Execute(int id) {
        if (!DataToRequest(id)) {
            return false;
        }
        network::RequestSender req_sender;
        std::string response = req_sender.Execute(request_, "/auth", false);
        if (response == "Error") {
            return false;
        }
        if (!ResponseToData(response)) {
            return false;
        }

        return true;
    }

    bool AuthorisationHandler::DataToRequest(int id) {
    try {
        boost::property_tree::ptree tree;
        tree.put("user_id", id);
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
    bool AuthorisationHandler::ResponseToData(std::string response) {
    try {
        std::stringstream buff;
        buff << response;
        boost::property_tree::ptree tree;
        boost::property_tree::read_json(buff, tree);
        output_.clear();
        for (auto& item : tree.get_child("chat_ids")) {
        output_.push_back(item.second.get_value<int>());
        }
    } catch (std::exception const& e) {
        std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
        return false;
    }
    return true;
    }    

}
