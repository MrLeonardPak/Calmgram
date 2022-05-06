#ifndef CALMGRAM_API_SERVER_JSON_PARSER_H
#define CALMGRAM_API_SERVER_JSON_PARSER_H

#include <memory>
#include <sstream>
#include <string>

namespace calmgram::api_server::json {

class JsonParser {
 public:
  JsonParser(std::string const& str);
  ~JsonParser();

  template <typename T>
  T GetValue(std::string const& name, T const& default_value) const;

 private:
  class JsonParserImpl;
  JsonParserImpl* p_impl_;
};

}  // namespace calmgram::api_server::json

#include "json_parser_impl.hpp"  // Подменой этого файла можно изменять реализацию

namespace json = ::calmgram::api_server::json;

json::JsonParser::JsonParser(std::string const& str)
    : p_impl_(new JsonParserImpl(str)){};

json::JsonParser::~JsonParser() {
  delete p_impl_;
}

template <typename T>
T json::JsonParser::GetValue(std::string const& name,
                             T const& default_value) const {
  return p_impl_->GetValue<T>(name, default_value);
}

#endif  // CALMGRAM_API_SERVER_JSON_PARSER_H