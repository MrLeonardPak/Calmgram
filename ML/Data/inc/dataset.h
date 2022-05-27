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

#include "interfaces_uc_output.h"

#define PATH_TO_DATA "../ML/files/data.txt"
#define PATH_TO_VOCAB "../ML/files/vocab.txt"
#define PATH_TO_IDFS "../ML/files/idfs.txt"
#define PATH_TO_ANSWERS "../ML/files/answers.txt"
#define PATH_TO_STOPWORDS "../ML/files/stopwords.txt"

namespace calmgram::ml::data {
class Dataset : public api_server::use_case::IAdditionalDataset {
  std::vector<std::string> data_;
  std::vector<std::string> unique_words_;
  std::vector<int> answers;
  std::vector<std::string> stopwords_;

 public:
  friend class Vectorizer;
  friend class NN;

  int numOfmsgAdded = 0;

  Dataset();
  void FillData();
  bool FillUniqueWords();
  void FillAnswers();
  void FillStopwords();

  bool CheckIfWordContains(const std::vector<std::string>& v,
                           const std::string& word);

  int GetAmountOfWordInDocs(const std::string& word) const;
  int GetAmountOfDocs() const;

  const std::vector<std::string> GetUniqueWords() const;
  const std::vector<std::string> GetData() const;

  void AdditionalDataset(std::string_view data, bool label) const override;

  int GetAmountOfUniqueWords() const;
  int GetNumOfMsgAdded() const;

  const std::vector<int> GetAnswers() const;

  void ExtractUniqueWords();

  ~Dataset() = default;
};
};  // namespace calmgram::ml::data

#endif
