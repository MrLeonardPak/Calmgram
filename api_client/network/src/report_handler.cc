#include "report_handler.h"

#include <iostream>

namespace calmgram::api_client::network {

bool ReportHandler::Execute(std::string msg,
                            bool is_marked,
                            std::string const& token) {
  if (!DataToRequest(msg, is_marked, token)) {
    return false;
  }
  network::RequestSender req_sender;
  std::string response = req_sender.Execute(request_, "/chat/ml", POST);
  if (response == "Error") {
    return false;
  }
  return true;
}

bool ReportHandler::DataToRequest(std::string msg,
                                  bool is_marked,
                                  std::string const& token) {
  try {
    boost::property_tree::ptree tree;
    tree.put("token", token);
    tree.put("is_marked", is_marked);
    tree.put("text", msg);
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
