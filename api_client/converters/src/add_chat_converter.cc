#include "add_chat_converter.h"

#include <iostream>

namespace calmgram::api_client::converters {

bool AddChatConverter::DataToRequest(int* ids,
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

bool AddChatConverter::ResponseToData(std::string response) {

  try {
    std::stringstream buff;
    buff << response;
    boost::property_tree::ptree tree;
    boost::property_tree::read_json(buff, tree);
    chat_id_ = tree.get<int>("chat_id");
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return false;
  }
  return true;
}

}  // namespace calmgram::api_client::converters

