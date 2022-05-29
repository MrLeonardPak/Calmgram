#include "dataset.h"

namespace calmgram::ml::data {

Dataset::Dataset() {
  numOfmsgAdded = 0;
  FillData();

  if (!FillUniqueWords()) {
    ExtractUniqueWords();
  }

  FillAnswers();

  FillStopwords();
}

void Dataset::FillStopwords() {
  std::ifstream file;
  file.open(PATH_TO_STOPWORDS);

  if (file.is_open()) {
    std::string buf;
    while (file >> buf) {
      stopwords_.push_back(buf);
    }
  }
  file.close();
}

void Dataset::ExtractUniqueWords() {
  std::ifstream file(PATH_TO_DATA);
  if (file.is_open()) {
    std::string buf;
    while (file >> buf) {
      if (buf == "")
        continue;
      std::istringstream ss(buf);
      std::string candidateToUnique;
      while (ss >> candidateToUnique) {
        if (!CheckIfWordContains(unique_words_, candidateToUnique)) {
          unique_words_.push_back(candidateToUnique);
        }
      }
    }
  }
}

void Dataset::FillAnswers() {
  std::ifstream file(PATH_TO_ANSWERS);
  int buf;
  if (file.is_open()) {
    while (file >> buf) {
      answers.push_back(buf);
    }
    file.close();
  }
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

bool Dataset::FillUniqueWords() {
  std::ifstream file;
  file.open(PATH_TO_VOCAB);
  std::string buf;
  if (file.is_open()) {
    while (file) {
      std::getline(file, buf);
      std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);

      if (buf == "" || CheckIfWordContains(unique_words_, buf) ||
          CheckIfWordContains(stopwords_, buf)) {
        continue;
      }

      unique_words_.push_back(buf);
    }
    file.close();
  } else {
    return false;
  }
  return true;
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

void Dataset::AdditionalDataset(std::string_view data, bool label) const {
  numOfmsgAdded += 1;

  std::ofstream fileSentences(PATH_TO_DATA, std::ios::app);
  fileSentences << data << std::endl;
  fileSentences.close();

  std::ofstream fileAnswers(PATH_TO_ANSWERS, std::ios::app);

  if (label) {
    fileAnswers << 1 << std::endl;
  } else {
    fileAnswers << 0 << std::endl;
  }

  fileAnswers.close();
}

const std::vector<int> Dataset::GetAnswers() const {
  return answers;
}

/*int GetNumOfMsgAdded() {
  return this->numOfmsgAdded;
}*/

}  // namespace calmgram::ml::data
