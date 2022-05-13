#ifndef VECTORIZER_H
#define VECTORIZER_H

#include "dataset.h"

namespace calmgram::ml::data {
class Vectorizer {
  std::vector<std::vector<float>> vect_data_;
  Dataset dataset;
  std::map<std::string, std::pair<int, float>> idfs;

 public:
  friend class NN;
  Vectorizer();
  void FillIdfs();
  void CreateIdfsFile();
  float GetTf(const std::string& word, const std::string& sentence) const;
  float GetIdf(const std::string& word) const;
  std::vector<float> GetVectorizedSentence(const std::string& sentence) const;
  std::string MakeLowercase(std::string sentence) const;
  std::string CleanSentence(std::string sentence) const;
  ~Vectorizer() = default;
};
}  // namespace calmgram::ml::data

#endif
