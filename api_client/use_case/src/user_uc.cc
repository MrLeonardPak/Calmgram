#include "user_uc.h"

#include <algorithm>
#include <stdexcept>

namespace calmgram::api_client::use_case {

void UserUseCase::Auth(int id) {
  if (!auth_->Execute(id)) {  // создаю(нахожу) пользователя на сервере
    throw std::invalid_argument("auth: error");
  }
  profile_.id = id;
  std::vector<int> chat_ids = auth_->GetData();
  for (int chat_id : chat_ids) {
    entities::Chat tmp_chat;
    tmp_chat.id = chat_id;
    if (!update_chat_->Execute(profile_.id, chat_id, 0)) {
      throw std::invalid_argument("update chat: error");
    }
    tmp_chat.messages = update_chat_->GetData();
    profile_.chats.push_back(tmp_chat);
  }
}

std::vector<int> UserUseCase::GetChats() {
  std::vector<int> chats;
  for (entities::Chat chat : profile_.chats) {
    chats.push_back(chat.id);
  }
  return chats;
}

std::vector<entities::Message> UserUseCase::OpenChat(int chat_id) {
  auto idx = std::find_if(
      profile_.chats.begin(), profile_.chats.end(),
      [=](entities::Chat const& chat) { return chat.id == chat_id; });
  if (idx != profile_.chats.end()) {
    return (*idx).messages;
  } else {
    std::vector<entities::Message> empty_msg_vec;
    return empty_msg_vec;
  }
}

int UserUseCase::CreateChat(std::vector<int> target_ids) {
  target_ids.push_back(profile_.id);
  if (!add_chat_->Execute(target_ids)) {
    throw std::invalid_argument("add chat: error");
  }
  entities::Chat tmp_chat;
  tmp_chat.id = add_chat_->GetData();
  profile_.chats.push_back(tmp_chat);
  return tmp_chat.id;
}

void UserUseCase::SendMessage(std::string str, int chat_id) {
  entities::Content content;
  content.type = entities::TEXT;
  content.data = str;
  if (!send_msg_->Execute(chat_id, profile_.id, content)) {
    throw std::invalid_argument("send msg: error");
  }
}

std::vector<int> UserUseCase::UpdateChats() {
  std::vector<int> updated_chats;
  if (!auth_->Execute(profile_.id)) {  // нахожу пользователя на сервере
    throw std::invalid_argument("auth: error");
  }
  std::vector<int> chat_ids = auth_->GetData();
  // создаю чаты в профиле если их не было
  for (size_t i = 0; i < chat_ids.size(); i++) {
    auto idx = std::find_if(
        profile_.chats.begin(), profile_.chats.end(),
        [=](entities::Chat const& chat) { return chat.id == chat_ids[i]; });

    if (idx == profile_.chats.end()) {
      entities::Chat tmp_chat;
      tmp_chat.id = chat_ids[i];
      if (!update_chat_->Execute(profile_.id, chat_ids[i], 0)) {
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
        std::find(chat_ids.begin(), chat_ids.end(), profile_.chats[i].id);

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
    if (!update_chat_->Execute(profile_.id, profile_.chats[i].id, last_time)) {
      throw std::invalid_argument("update chat: error");
    }
    std::vector<entities::Message> new_messages;
    new_messages = update_chat_->GetData();
    if (!new_messages.empty()) {
      profile_.chats[i].messages.insert(profile_.chats[i].messages.end(),
                                        new_messages.begin(),
                                        new_messages.end());
      updated_chats.push_back(profile_.chats[i].id);
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

void UserUseCase::ReportAboutMark(std::string msg, bool is_marked) {
  if (!report_->Execute(msg, is_marked)) {
    throw std::invalid_argument("report: error");
  }
}
}  // namespace calmgram::api_client::use_case
