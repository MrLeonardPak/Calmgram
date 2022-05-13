#ifndef DATASET_H
#define DATASET_H

#include <math.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <cassert>

#define PATH_TO_DATA "../ML/files/data.txt"
#define PATH_TO_VOCAB "../ML/files/vocab.txt"
#define PATH_TO_IDFS "../ML/files/idfs.txt"

namespace calmgram::ml::data {
class Dataset {
  std::vector<std::string> data_;
  std::vector<std::string> unique_words_;

 public:
  friend class Vectorizer;
  friend class NN;

  Dataset();
  void FillData();
  void FillUniqueWords();
  bool CheckIfWordContains(const std::vector<std::string>& v,
                           const std::string& word);
  int GetAmountOfWordInDocs(const std::string& word) const;
  int GetAmountOfDocs() const;
  const std::vector<std::string> GetUniqueWords() const;
  const std::vector<std::string> GetData() const;
  int GetAmountOfUniqueWords() const;
  ~Dataset() = default;
};
};  // namespace calmgram::ml::data

#endif