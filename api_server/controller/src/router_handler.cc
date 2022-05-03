#include "controller.h"

namespace calmgram::api_server::controller {

void RegisterHandler(std::unique_ptr<IHandler> handler) {
  // TODO: Добавляет в хэш таблицу
}

Response Controller::ExecuteHandler(Request const& request) {
  // TODO: Проверяет хэш таблице
}

}  // namespace calmgram::api_server::controller
