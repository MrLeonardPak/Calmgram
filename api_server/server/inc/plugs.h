#ifndef CALMGRAM_API_SERVER_PLUGS_H
#define CALMGRAM_API_SERVER_PLUGS_H

#include "controller.h"
#include "interfaces_uc_input.h"
#include "interfaces_uc_output.h"

#include <boost/core/ignore_unused.hpp>

namespace calmgram::api_server::server {

class AdminHandler : public controller::IHandler {
 public:
  controller::Response Handle(controller::IRequest const& request) {
    std::cout << "FROM: " << request.get_path() << std::endl;
    std::cout << "BODY: " << request.get_body() << std::endl;
    return {controller::Response::OK, "Oh My God!"};
  }
};

// class TestGetUser : public use_case::IGetUser {
//  public:
//   entities::User GetUser(int id) const override {
//     std::vector<int> chats;
//     size_t chats_count = rand() % 5 + 1;
//     for (size_t i = 0; i < chats_count; ++i) {
//       chats.push_back(id + i);
//     }
//     auto user = entities::User{.id = id, .chats = chats};
//     return user;
//   }

//  private:
// };

// class TestCheckUserAccessToChat : public use_case::ICheckUserAccessToChat {
//  public:
//   bool CheckUserAccessToChat(int user_id, int chat_id) const override {
//     ::boost::ignore_unused(user_id);
//     ::boost::ignore_unused(chat_id);
//   }
// };

// class TestCreateUser : public use_case::ICreateUser {
//  public:
//   entities::User CreateUser(int id) const override {
//     auto user = entities::User{.id = id, .chats = {}};
//     return user;
//   }
// };

// class TestSetChat : public use_case::ISetChat {
//  public:
//   void SetChat(std::vector<int> const& users, int chat_id) const override {
//     ::boost::ignore_unused(users);
//     ::boost::ignore_unused(chat_id);
//   }
// };

// class TestCreateChat : public use_case::ICreateChat {
//  public:
//   int CreateChat() const override { return 123; }
// };

// class TestGetMsgs : public use_case::IGetMsgs {
//  public:
//   std::vector<entities::Message> GetMsgs(int chat_id,
//                                          time_t from_time) const override {
//     auto msgs = std::vector<entities::Message>();
//     size_t msg_cnt = rand() % 3;
//     for (size_t i = 0; i < msg_cnt; ++i) {
//       auto user_id_tmp = (i % 2) ? 10 : 20;
//       entities::Content content_tmp("Some text " + std::to_string(i));
//       time_t from_time_tmp = from_time + i * chat_id;
//       auto mark_tmp = (i % 2) ? true : false;
//       msgs.push_back({user_id_tmp, from_time_tmp, content_tmp, mark_tmp});
//     }
//     return msgs;
//   }
// };

// class TestSendMsg : public use_case::ISendMsg {
//  public:
//   void SendMsg(entities::Message const& msg, int chat_id) const override {
//     // ::boost::ignore_unused(msg);
//     ::boost::ignore_unused(chat_id);
//     std::cout << "Message: " << msg.content.text << '\n';
//     std::cout << "Mark: " << (msg.is_marked ? "true" : "false") << '\n';
//   }
// };

class TestAnalysisText : public use_case::IAnalysisText {
 public:
  bool AnalysisText(std::string_view msg) const override {
    return msg[0] == '!';
  }
};

class TestAdditionalDataset : public use_case::IAdditionalDataset {
 public:
  void AdditionalDataset(std::string_view const& data,
                         bool label) const override {
    ::boost::ignore_unused(data);
    ::boost::ignore_unused(label);
  }
};

}  // namespace calmgram::api_server::server

#endif  // CALMGRAM_API_SERVER_PLUGS_H