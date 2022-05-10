#include "add_chat_converter.h"

namespace calmgram::api_client::converters {

    bool AddChatConverter::DataToRequest(int id_1, int id_2) { // добавить обработку ошибок
        boost::property_tree::ptree tree;
        tree.put("id_1",id_1);
        tree.put("id_2",id_2);
        std::ostringstream buf; 
        write_json (buf, tree, false);
        std::string json = buf.str();

        std::string request = "POST /chat/add HTTP/1.1 \n";
        request += "Content-Type: application/json\n";
        request += "Accept: */*\n";
        request += "Content-Length: "; 
        request += json.length(); 
        request += "\n\n";
        request += json;
               
        request_ = request;
        return true;
        
    }

    bool AddChatConverter::ResponseToData(std::string response) {
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
        chat_id_ = tree.get<int>("chat_id");
        return true;
    }

} // namespace calmgram::api_client::convertersx