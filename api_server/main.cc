#include "server_core.h"

#include <memory>

int main() {
  std::make_unique<calmgram::api_server::server::ServerCore>()->Run();
  return 0;
}