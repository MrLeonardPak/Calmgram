#ifndef VECTORIZER_H
#define VECTORIZER_H

#include "dataset.h"

namespace calmgram::ml::data {
class Vectorizer {

  std::vector<std::vector<double>> vect_data_;
  Dataset dataset;
  std::map<std::string, std::pair<int, double>> idfs;

 public:
  friend class NN;

  Vectorizer();
  void FillIdfs();
  void CreateIdfsFile();

  double GetTf(const std::string& word, const std::string& sentence) const;
  double GetIdf(const std::string& word) const;

  std::vector<double> GetVectorizedSentence(const std::string& sentence) const;
  std::string MakeLowercase(std::string sentence) const;
  std::string CleanSentence(std::string sentence) const;

  const std::vector<std::vector<double>> GetVectorizedData() const;

  std::vector<double> NormalizeSentence(std::vector<double> vectSentence);
  
  ~Vectorizer() = default;
};
}  // namespace calmgram::ml::data

#endif
