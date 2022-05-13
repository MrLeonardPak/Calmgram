#ifndef CALMGRAM_API_SERVER_LIBS_BOOST_JSON_PARSER_IMPL_HPP
#define CALMGRAM_API_SERVER_LIBS_BOOST_JSON_PARSER_IMPL_HPP

#include <any>
#include <sstream>
#include <string>
#include <unordered_map>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_server::json {

class JsonParser {
 public:
  JsonParser(std::string const& str) {
    std::stringstream in(str);
    boost::property_tree::read_json(in, pt_);
  }

  void Refresh() { pt_.erase(pt_.begin()); };

  template <typename T>
  T GetValue(std::string const& name) const {
    return pt_.get<T>(name);
  }

  template <typename T>
  std::vector<T> GetVector(std::string const& name) const;

  std::string GetString() const;

  template <typename T>
  void SetValue(std::string const& name, T const& value);

  template <typename T>
  void SetVector(std::string name, std::vector<T> vector);

 private:
  boost::property_tree::ptree pt_;

  template <typename T>
  boost::property_tree::ptree ParseEntity(T entity);
};

template <>
boost::property_tree::ptree JsonParser::ParseEntity<entities::Message>(
    entities::Message entity) {
  boost::property_tree::ptree pt_structure;
  pt_structure.put("owner_id", entity.owner_id);
  pt_structure.put("created", entity.created);
  pt_structure.put("is_marked", entity.is_marked);
  pt_structure.put("text", entity.content.text);

  return pt_structure;
}

template <typename T>
std::vector<T> JsonParser::GetVector(std::string const& name) const {
  boost::property_tree::ptree pt_vector = pt_.get_child(name);
  auto out_vector = std::vector<T>();
  for (auto const& [_, value] : pt_vector) {
    out_vector.push_back(value.template get_value<int>());
  }
  return out_vector;
}

std::string JsonParser::GetString() const {
  std::stringstream out;
  boost::property_tree::write_json(out, pt_);
  return out.str();
}

template <typename T>
void JsonParser::SetValue(std::string const& name, T const& value) {
  pt_.put(name, value);
}

template <typename T>
void JsonParser::SetVector(std::string name, std::vector<T> vector) {
  boost::property_tree::ptree children;
  for (auto const& element : vector) {
    boost::property_tree::ptree pt_tmp;
    pt_tmp.put("", element);
    children.push_back(std::make_pair("", pt_tmp));
  }
  pt_.add_child(name, children);
}

template <>
void JsonParser::SetVector<entities::Message>(
    std::string name,
    std::vector<entities::Message> vector) {
  boost::property_tree::ptree children;
  for (auto const& entity : vector) {
    children.push_back(std::make_pair("", ParseEntity(entity)));
  }
  pt_.add_child(name, children);
}

}  // namespace calmgram::api_server::json

#endif  // CALMGRAM_API_SERVER_LIBS_BOOST_JSON_PARSER_IMPL_HPP