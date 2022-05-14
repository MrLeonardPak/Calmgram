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
  for (size_t i = 0; i < chat_ids.size(); i++) {  // создаю чаты в профиле
    entities::Chat tmp_chat;
    tmp_chat.id = chat_ids[i];
    if (!update_chat_->Execute(profile_.id, chat_ids[i], 0)) {
      throw std::invalid_argument("update chat: error");
    }
    tmp_chat.messages = update_chat_->GetData();
    profile_.chats.push_back(tmp_chat);
  }
}

std::vector<int> UserUseCase::GetChats() {
  std::vector<int> chats;
  for (size_t i = 0; i < profile_.chats.size(); i++) {
    chats.push_back(profile_.chats[i].id);
  }
  return chats;
}

std::vector<entities::Message> UserUseCase::OpenChat(int chat_id) {
  size_t idx = 0;
  while (idx < profile_.chats.size() && chat_id != profile_.chats[idx].id) {
    idx++;
  }
  if (idx < profile_.chats.size()) {
    return profile_.chats[idx].messages;
  } else {
    std::vector<entities::Message> empty_msg_vec;
    return empty_msg_vec;
  }
}

bool UserUseCase::CreateChat(int target_id) {
  if (!add_chat_->Execute(profile_.id, target_id)) {
    throw std::invalid_argument("add chat: error");
  }
  if (add_chat_->GetData() == 0) {  // если чат не создан из-за сервера (нет
                                    // ползователя с targed_id или проч.)
    return false;
  }
  entities::Chat tmp_chat;
  tmp_chat.id = add_chat_->GetData();
  profile_.chats.push_back(tmp_chat);
  return true;
}

bool UserUseCase::SendMessage(std::string str, int chat_id) {
  entities::Content content;
  content.type = entities::TEXT;
  content.data = str;
  if (!send_msg_->Execute(chat_id, profile_.id, content)) {
    throw std::invalid_argument("send msg: error");
  }
  return send_msg_->GetData();
}

std::vector<int> UserUseCase::UpdateChats() {
  std::vector<int> updated_chats;
  for (size_t i = 0; i < profile_.chats.size();
       i++) {  // проверка каждого чата на обновление
    if (!update_chat_->Execute(profile_.id, profile_.chats[i].id, time(NULL))) {
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
  if (!auth_->Execute(profile_.id)) {  // нахожу пользователя на сервере
    throw std::invalid_argument("auth: error");
  }
  std::vector<int> chat_ids = auth_->GetData();

  // создаю чаты в профиле если их не было
  for (size_t i = 0; i < chat_ids.size(); i++) {
    size_t j = 0;
    bool is_finded = false;
    while (j < profile_.chats.size() && !is_finded) {
      if (profile_.chats[j].id == chat_ids[i]) {
        is_finded = true;
      }
      j++;
    }
    if (!is_finded) {
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
  for (size_t i = 0; i < profile_.chats.size(); i++) {
    size_t j = 0;
    bool is_finded = false;
    while (j < chat_ids.size() && !is_finded) {
      if (chat_ids[j] == profile_.chats[i].id) {
        is_finded = true;
      }
      j++;
    }
    if (!is_finded) {
      profile_.chats.erase(profile_.chats.begin() + i);
      i--;
    }
  }
  return updated_chats;
}

}  // namespace calmgram::api_client::use_case
