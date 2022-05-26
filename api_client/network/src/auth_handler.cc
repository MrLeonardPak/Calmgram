#include "auth_handler.h"

#include <iostream>

namespace calmgram::api_client::network {

bool AuthorisationHandler::Execute(std::string const& login,
                                   std::string const& password) {
  if (!DataToRequest(login, password)) {
    return false;
  }
  network::RequestSender req_sender;
  std::string response = req_sender.Execute(request_, "/auth", CONNECT);
  if (response == "Error") {
    return false;
  }
  if (!ResponseToData(response)) {
    return false;
  }

  return true;
}

bool AuthorisationHandler::DataToRequest(std::string const& login,
                                         std::string const& password) {
  try {
    boost::property_tree::ptree tree;
    tree.put("login", login);
    tree.put("password", password);
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
    output_ = tree.get<std::string>("token");
  } catch (std::exception const& e) {
    std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
    return false;
  }
  return true;
}

}  // namespace calmgram::api_client::network
