#include "update_chat_converter.h"

namespace calmgram::api_client::converters {

    bool UpdateChatConverter::DataToRequest(int user_id, int chat_id, time_t last_update) {
        boost::property_tree::ptree tree;
        tree.put("user_id", user_id);
        tree.put("chat_id", chat_id);
        tree.put("from_time", last_update);
        std::ostringstream buf; 
        write_json (buf, tree, false);
        std::string json = buf.str();
               
        request_ = json;
        return true;
    }
    bool UpdateChatConverter::ResponseToData(std::string response) {
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
        std::vector<entities::Message> buf_msgs;
        for (auto& item : tree.get_child("msgs")) {
            entities::Message buf_msg;
            buf_msg.owner_id =  item.second.get<int>("owner");
            buf_msg.is_marked = item.second.get<bool>("is_marked");
            buf_msg.time = item.second.get<time_t>("created");
            if (item.second.get<std::string>("type") == "txt") {
                buf_msg.content.type = entities::TEXT;
                buf_msg.content.data = item.second.get<std::string>("content");
            } else {
                buf_msg.content.type = entities::JPEG;
                // вызвать хендлер для получения изображения
            }
            buf_msgs.push_back(buf_msg);
            
        }
        return true;
    }

} // namespace calmgram::api_client::converters