#ifndef CALMGRAM_API_SERVER_CORE_H
#define CALMGRAM_API_SERVER_CORE_H

namespace calmgram::api_server::server {
// TODO: класс CoreServer который через умные указатели  создает все интрефейсы
// и передает в юз-кейсы и ...
class ServerCore {
 public:
  void Run();
};

}  // namespace calmgram::api_server::server

#endif  // CALMGRAM_API_SERVER_CORE_H