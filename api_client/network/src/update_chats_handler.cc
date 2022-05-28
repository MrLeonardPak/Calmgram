#include "update_chats_handler.h"

#include <iostream>

namespace calmgram::api_client::network {

bool UpdateChatsHandler::Execute(std::string const& token) {
  if (!DataToRequest(token)) {
    return false;
  }
  network::RequestSender req_sender;
  std::string response = req_sender.Execute(request_, "/chat/list", GET);
  if (response == "Error") {
    return false;
  }
  if (!ResponseToData(response)) {
    return false;
  }
  return true;
}

bool UpdateChatsHandler::DataToRequest(std::string const& token) {
  try {
    boost::property_tree::ptree tree;
    tree.put("token", token);

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

bool UpdateChatsHandler::ResponseToData(std::string response) {
  try {
    std::stringstream buff;
    buff << response;
    boost::property_tree::ptree tree;
    boost::property_tree::read_json(buff, tree);
    output_.clear();
    for (auto& item : tree.get_child("chats")) {
      entities::EmptyChat buf_chat;
      buf_chat.id = item.second.get<int>("id");
      for (auto& login : item.second.get_child("user_logins")) {
        buf_chat.companions.push_back(login.second.get_value<std::string>());
      }
      output_.push_back(buf_chat);
    }
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return false;
  }
  return true;
}

}  // namespace calmgram::api_client::network