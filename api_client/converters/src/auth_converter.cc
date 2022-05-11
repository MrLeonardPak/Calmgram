#include "auth_converter.h"

#include <iostream>
namespace calmgram::api_client::converters {

bool AuthorisationConverter::DataToRequest(int id) {
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
bool AuthorisationConverter::ResponseToData(std::string response) {
  try {
    std::stringstream buff;
    buff << response;
    boost::property_tree::ptree tree;
    boost::property_tree::read_json(buff, tree);
    for (auto& item : tree.get_child("chats")) {
      chat_id_.push_back(item.second.get_value<int>());
    }
  }catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return false;
  }
  return true;
}

}  // namespace calmgram::api_client::converters
