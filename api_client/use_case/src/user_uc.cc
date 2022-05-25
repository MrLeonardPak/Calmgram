#include "user_uc.h"

#include <algorithm>
#include <stdexcept>

namespace calmgram::api_client::use_case {

void UserUseCase::Auth(std::string const& login, std::string const& password) {
  if (!auth_->Execute(login, password)) {  // создаю(нахожу) пользователя на сервере
    throw std::invalid_argument("auth: error");
  }
  profile_.login = login;
  profile_.password = password;
  profile_.token = auth_->GetData();
  if (!update_chats_->Execute(profile_.token)) {
    throw std::invalid_argument("update chats: error");
  }
  std::vector<entities::EmptyChat> chats = update_chats_->GetData();
  for (entities::EmptyChat chat : chats) {
    entities::Chat tmp_chat;
    tmp_chat.id = chat.id;
    tmp_chat.companions = chat.companions;
    if (!update_chat_->Execute(chat.id, 0,  profile_.token)) {
      throw std::invalid_argument("update chat: error");
    }
    tmp_chat.messages = update_chat_->GetData();
    profile_.chats.push_back(tmp_chat);
  }
}

std::vector<entities::EmptyChat> UserUseCase::GetChats() const {
  std::vector<entities::EmptyChat> chats;
  for (entities::Chat chat : profile_.chats) {
    entities::EmptyChat tmp_chat;
    tmp_chat.id = chat.id;
    tmp_chat.companions = chat.companions;
    chats.push_back(tmp_chat);
  }
  return chats;
}

std::vector<entities::Message> UserUseCase::OpenChat(int chat_id) const {
  auto idx = std::find_if(
      profile_.chats.begin(), profile_.chats.end(),
      [=](entities::Chat const& chat) { return chat.id == chat_id; });
  if (idx != profile_.chats.end()) {
    return (*idx).messages;
  } else {
    throw std::invalid_argument("This chat don't exist");
  }
}

void UserUseCase::CreateChat(std::vector<std::string> const& target_logins) const {
  if (!add_chat_->Execute(target_logins,  profile_.token)) {
    throw std::invalid_argument("add chat: error");
  }
}

void UserUseCase::SendMessage(std::string const& str, int chat_id) const {
  entities::Content content;
  content.type = entities::TEXT;
  content.data = str;
  if (!send_msg_->Execute(chat_id, content, profile_.token)) {
    throw std::invalid_argument("send msg: error");
  }
}

std::vector<entities::EmptyChat> UserUseCase::UpdateChats() {
  std::vector<entities::EmptyChat> updated_chats;
  if (!update_chats_->Execute(profile_.token)) {  // нахожу пользователя на сервере
    throw std::invalid_argument("auth: error");
  }
  std::vector<entities::EmptyChat> chat_ids = update_chats_->GetData();
  // создаю чаты в профиле если их не было
  for (size_t i = 0; i < chat_ids.size(); i++) {
    auto idx = std::find_if(
        profile_.chats.begin(), profile_.chats.end(),
        [=](entities::Chat const& chat) { return chat.id == chat_ids[i].id; });

    if (idx == profile_.chats.end()) {
      entities::Chat tmp_chat;
      tmp_chat.id = chat_ids[i].id;
      tmp_chat.companions = chat_ids[i].companions;
      if (!update_chat_->Execute(chat_ids[i].id, 0, profile_.token)) {
        throw std::invalid_argument("update chat: error");
      }
      tmp_chat.messages = update_chat_->GetData();
      profile_.chats.push_back(tmp_chat);
      updated_chats.push_back(chat_ids[i]);
    }
  }
  // удаляю чаты если их нет на сервере
  for (size_t i = 0; i < profile_.chats.size();) {
    auto idx =
        std::find_if(chat_ids.begin(), chat_ids.end(),
        [=](entities::EmptyChat const& chat) { return chat.id == profile_.chats[i].id; });

    if (idx != chat_ids.end()) {
      i++;
    } else {
      profile_.chats.erase(profile_.chats.begin() + i);
    }
  }
  for (size_t i = 0; i < profile_.chats.size();
       i++) {  // проверка каждого чата на обновление
    time_t last_time = (profile_.chats[i].messages.empty()
                            ? 0
                            : profile_.chats[i].messages.back().time);
    if (!update_chat_->Execute(profile_.chats[i].id, last_time, profile_.token)) {
      throw std::invalid_argument("update chat: error");
    }
    std::vector<entities::Message> new_messages;
    new_messages = update_chat_->GetData();
    if (!new_messages.empty()) {
      profile_.chats[i].messages.insert(profile_.chats[i].messages.end(),
                                        new_messages.begin(),
                                        new_messages.end());
      entities::EmptyChat tmp_chat;
      tmp_chat.id = profile_.chats[i].id;
      tmp_chat.companions = profile_.chats[i].companions;
      updated_chats.push_back(tmp_chat);
    }
  }
  std::sort(
      profile_.chats.begin(), profile_.chats.end(),
      [](entities::Chat const& chat_1, entities::Chat const& chat_2) {
        return (!chat_1.messages.empty() ? chat_1.messages.back().time : 0) >
               (!chat_2.messages.empty() ? chat_2.messages.back().time : 0);
      });
  return updated_chats;
}

void UserUseCase::ReportAboutMark(std::string const& msg, bool is_marked) const {
  if (!report_->Execute(msg, is_marked, profile_.token)) {
    throw std::invalid_argument("report: error");
  }
}
}  // namespace calmgram::api_client::use_case
