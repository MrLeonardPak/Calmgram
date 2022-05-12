#include "dataset.h"

namespace calmgram::ml::data {
    template <typename MsgType>
    Dataset<MsgType>::Dataset() {
        FillData();
        FillUniqueWords();
    }
    template <typename MsgType>
    void Dataset<MsgType>::FillData() {
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
    }
  }
    template <typename MsgType>
    void Dataset<MsgType>::FillUniqueWords() {
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
    template <typename MsgType>
    bool Dataset<MsgType>::CheckIfWordContains(const std::vector<MsgType>& v, const MsgType& word) const {
        return std::find(v.begin(), v.end(), word) != v.end();
    }

    template <typename MsgType>
    const int Dataset<MsgType>::GetAmountOfWordInDocs(const MsgType& word) const {
    int res = 0;
    MsgType buf;

    for (int i = 0; i < data_.size(); ++i) {
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
    template <typename MsgType>
    const int Dataset<MsgType>::GetAmountOfDocs() const { 
        return data_.size(); 
    }

    template <typename MsgType>
    const std::vector<MsgType> Dataset<MsgType>::GetUniqueWords() const { 
        return unique_words_; 
    }

    template <typename MsgType>
    const std::vector<MsgType> Dataset<MsgType>::GetData() const { 
        return data_; 
    }

    template <typename MsgType>
    const int Dataset<MsgType>::GetAmountOfUniqueWords() const { 
        return unique_words_.size(); 
    }

}

