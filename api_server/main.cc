#include "server_core.h"

#include <iostream>
#include <memory>

int main() {
  // std::make_unique<calmgram::api_server::server::ServerCore>()->Run();
  // try {
  //   auto db = calmgram::api_server::libs::database::PostgreSQL(
  //       "user=calmgram host=localhost port=5432 password=calmgram "
  //       "dbname=calmgram",
  //       "/home/leonard/technopark/sem_1/Calmgram/api_server/libs/database/"
  //       "initialScript.sql");

  //   auto user = db.CreateUser(123);
  //   std::cout << user.id << " : " << user.chats.size() << '\n';

  //   auto chat_id = db.CreateChat();
  //   std::cout << "new chat: " << chat_id << '\n';

  //   db.SetChat({user.id}, chat_id);

  //   std::cout << "check chat: " << db.CheckUserAccessToChat(user.id, chat_id)
  //             << '\n';

  //   user = db.GetUser(123);
  //   std::cout << user.id << " : " << user.chats.size() << '\n';

  //   auto msg = calmgram::api_server::entities::Message(
  //       user.id,
  //       std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
  //       {"hellp"}, false);
  //   db.SendMsg(msg, chat_id);

  //   auto msgs = db.GetMsgs(chat_id, 0);
  //   for (auto&& msg : msgs) {
  //     std::cout << msg.owner_id << " : " << msg.content.text << "\n";
  //   }

  // } catch (const std::exception& e) {
  //   std::cout << __FILE__ << ':' << __LINE__ << ": " << e.what() << '\n';
  // }
  return 0;
}