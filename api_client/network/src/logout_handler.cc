#include "logout_handler.h"

#include <iostream>

namespace calmgram::api_client::network {

bool LogoutHandler::Execute(std::string const& token) {
  if (!DataToRequest(token)) {
    return false;
  }
  network::RequestSender req_sender;
  std::string response = req_sender.Execute(request_, "/logout", POST);
  if (response == "Error") {
    return false;
  }
  return true;
}

bool LogoutHandler::DataToRequest(std::string const& token) {
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

}  // namespace calmgram::api_client::network
