#include "auth_converter.h"

namespace calmgram::api_client::converters {

    bool AuthorisationConverter::DataToRequest(int id) {
        boost::property_tree::ptree tree;
        tree.put("id",id);
        std::ostringstream buf; 
        write_json (buf, tree, false);
        std::string json = buf.str();
               
        request_ = json;
        return true;
    }
    bool AuthorisationConverter::ResponseToData(std::string response) {
        response.erase(0, 9);
        if (response[0] == '4') {
            return false;
        }
        while (response[0] != '\n' && response[1] != '\n') {
            response.erase(0, 1);
        }
        response.erase(0, 2);
        
        std::stringstream buff;
        buff << response;
        boost::property_tree::ptree tree;
        boost::property_tree::read_json(buff, tree);
        for (auto& item : tree.get_child("chat_arr")) {
            chat_id_.push_back(item.second.get_value<int>());
        }
        return true;
    }

} // namespace calmgram::api_client::converters

