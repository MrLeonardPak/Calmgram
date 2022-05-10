#include "send_msg_converter.h"
#include "entities.h"

namespace calmgram::api_client::converters {

    bool SendMessageConverter::DataToRequest(int chat_id, int user_id, entities::Content content) {
        boost::property_tree::ptree tree;
        tree.put("chat_id",chat_id);
        tree.put("user_id",123);
        if (content.type == entities::TEXT) {
            tree.put("text",content.data);
            tree.put("image", "");
        } else {
            tree.put("text", "");
            tree.put("image", content.data);
        }
        std::ostringstream buf; 
        write_json (buf, tree, false);
        std::string json = buf.str();

        std::string request = "POST /chat/send HTTP/1.1 \n";
        request += "Content-Type: application/json\n";
        request += "Accept: */*\n";
        request += "Content-Length: "; 
        request += json.length(); 
        request += "\n\n";
        request += json;
               
        request_ = request;
        return true;
    }
    bool SendMessageConverter::ResponseToData(std::string response) {
        response.erase(0, 9);
        if (response[0] == '4') {
            return false;
        }
        return true;
    }

} // namespace calmgram::api_client::converters