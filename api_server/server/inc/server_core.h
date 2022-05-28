#ifndef CALMGRAM_API_SERVER_CORE_H
#define CALMGRAM_API_SERVER_CORE_H

namespace calmgram::api_server::server {

class ServerCore {
 public:
  void Run();

 private:
  auto constexpr static kConnectionDB = "CALMGRAM_CONNECTION_DB";
  auto constexpr static kInitionalDB = "CALMGRAM_INITIONAL_DB";
  auto constexpr static kHost = "CALMGRAM_HOST";
  auto constexpr static kPort = "CALMGRAM_PORT";
};

}  // namespace calmgram::api_server::server

#endif  // CALMGRAM_API_SERVER_CORE_H