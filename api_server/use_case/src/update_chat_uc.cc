#include "update_chat_uc.h"

namespace calmgram::api_server::use_case {

std::vector<entities::Message> UpdateChatUC::Execute() {
  std::vector<entities::Message> tmp;
  tmp.push_back(entities::Message());
  return tmp;
}

}  // namespace calmgram::api_server::use_case
