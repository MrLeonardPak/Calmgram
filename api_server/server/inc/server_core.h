#ifndef CALMGRAM_API_SERVER_CORE_H
#define CALMGRAM_API_SERVER_CORE_H

#include "controller.h"
#include "interfaces_uc_input.h"
#include "interfaces_uc_output.h"

#include <boost/core/ignore_unused.hpp>

namespace calmgram::api_server::server {
// TODO: класс CoreServer который через умные указатели  создает все интрефейсы
// и передает в юз-кейсы и ...
class ServerCore {
 public:
  void Run();
};

// HACK: Классы для тестов
class AdminHandler : public controller::IHandler {
 public:
  controller::Response Handle(controller::IRequest const& request) {
    std::cout << "FROM: " << request.get_path() << std::endl;
    std::cout << "BODY: " << request.get_body() << std::endl;
    return {controller::Response::OK, "Oh My God!"};
  }
};
// TODO: Тестовые заглушки сценариев
class TestGetUser : public use_case::IGetUser {
 public:
  entities::User GetUser(int id) const override {
    auto user = entities::User{.id = id, .chats = {1, 2, 3, 0, 0, id}};
    return user;
  }
};

class TestCheckUser : public use_case::ICheckUser {
 public:
  void CheckUser(int id) const override { ::boost::ignore_unused(id); }
};

class TestCreateUser : public use_case::ICreateUser {
 public:
  entities::User CreateUser(int id) const override {
    auto user = entities::User{.id = id, .chats = {}};
    return user;
  }
};

class TestSetChat : public use_case::ISetChat {
 public:
  void SetChat(std::vector<int> const& users, int chat_id) const override {
    ::boost::ignore_unused(users);
    ::boost::ignore_unused(chat_id);
  }
};

class TestCreateChat : public use_case::ICreateChat {
 public:
  int CreateChat() const override { return 123; }
};

class TestGetMsgs : public use_case::IGetMsgs {
 public:
  std::vector<entities::Message> GetMsgs(int chat_id,
                                         time_t from_time) const override {
    auto msgs = std::vector<entities::Message>();
    auto const msg_cnt = 10;
    for (size_t i = 0; i < msg_cnt; ++i) {
      auto user_id_tmp = (i > msg_cnt / 2) ? 10 : 20;
      entities::Content content_tmp("Some text " + std::to_string(i),
                                    entities::TEXT);
      time_t from_time_tmp = from_time + i * chat_id;
      auto mark_tmp = (i > msg_cnt / 2) ? true : false;
      msgs.push_back({user_id_tmp, from_time_tmp, content_tmp, mark_tmp});
    }
    return msgs;
  }
};

class TestSendMsg : public use_case::ISendMsg {
 public:
  void SendMsg(entities::Message const& msg, int chat_id) const override {
    ::boost::ignore_unused(msg);
    ::boost::ignore_unused(chat_id);
  }
};

class TestAnalysisText : public use_case::IAnalysisText {
 public:
  bool AnalysisText(std::string const& msg) const override {
    return msg[0] == '!';
  }
};

}  // namespace calmgram::api_server::server

#endif  // CALMGRAM_API_SERVER_CORE_H