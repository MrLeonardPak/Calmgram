#include "update_chat_uc.h"

namespace calmgram::api_server::use_case {

std::vector<entity::Message> UpdateChatUC::Execute() {
  std::vector<entity::Message> tmp;
  tmp.push_back(entity::Message());
  return tmp;
}

}  // namespace calmgram::api_server::use_case
