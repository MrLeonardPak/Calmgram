#ifndef CALMGRAM_API_SERVER_USE_CASE_SEND_MSG_H
#define CALMGRAM_API_SERVER_USE_CASE_SEND_MSG_H

#include "interfaces_use_case.h"

namespace calmgram::api_server::use_case {

class SendMsgUC {
 private:
  int user_id_;
  int chat_id_;
  entities::Content content_;
  IGetUser& getter_user_;
  IAnalysisText& analizer_text_;
  ISendMsg& sender_msg_;

 public:
  SendMsgUC(int user_id,
            int chat_id,
            entities::Content content,
            IGetUser& getter_user,
            IAnalysisText& analizer_text,
            ISendMsg& sender_msg)
      : user_id_(user_id),
        chat_id_(chat_id),
        content_(content),
        getter_user_(getter_user),
        analizer_text_(analizer_text),
        sender_msg_(sender_msg) {}
  ~SendMsgUC() {}

  void Execute();
};

}  // namespace calmgram::api_server::use_case

#endif  // CALMGRAM_API_SERVER_USE_CASE_SEND_MSG_H