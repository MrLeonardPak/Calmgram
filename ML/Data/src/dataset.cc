#include "dataset.h"

namespace calmgram::ml::data {

Dataset::Dataset() {
  FillData();
  FillUniqueWords();
}

void Dataset::FillData() {
  std::ifstream file;

  file.open(PATH_TO_DATA);
  std::string buf;

  if (file.is_open()) {
    while (file) {
      std::getline(file, buf);
      std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
      if (buf == "") {
        continue;
      }
      data_.push_back(buf);
    }
    file.close();
  } else {
    puts("FAIL");
  }
}

void Dataset::FillUniqueWords() {
  std::ifstream file;
  file.open(PATH_TO_VOCAB);
  std::string buf;
  if (file.is_open()) {
    while (file) {
      std::getline(file, buf);
      std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);

      if (buf == "" && CheckIfWordContains(unique_words_, buf)) {
        continue;
      }

      unique_words_.push_back(buf);
    }
    file.close();
  }
}

bool Dataset::CheckIfWordContains(const std::vector<std::string>& v,
                                  const std::string& word) {
  return std::find(v.begin(), v.end(), word) != v.end();
}

int Dataset::GetAmountOfWordInDocs(const std::string& word) const {
  int res = 0;
  std::string buf;

  for (size_t i = 0; i < data_.size(); ++i) {
    std::istringstream ss(data_[i]);
    while (ss >> buf) {
      if (word == buf) {
        res += 1;
        continue;
      }
    }
  }
  return res;
}

int Dataset::GetAmountOfDocs() const {
  return data_.size();
}

const std::vector<std::string> Dataset::GetUniqueWords() const {
  return unique_words_;
}

const std::vector<std::string> Dataset::GetData() const {
  return data_;
}

int Dataset::GetAmountOfUniqueWords() const {
  return unique_words_.size();
}

}  // namespace calmgram::ml::data
