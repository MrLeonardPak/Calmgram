#include "vectorizer.h"

namespace calmgram::ml::data {

bool CheckIfFileExists(std::string filename) {
  std::ifstream f(filename.c_str());
  return f.good();
}

Vectorizer::Vectorizer() {
  if (!CheckIfFileExists(PATH_TO_IDFS)) {
    CreateIdfsFile();
    FillIdfs();
  } else {
    FillIdfs();
  }

  std::vector<float> vect_sentence(dataset.GetAmountOfUniqueWords(), 0);
  for (size_t i = 0; i < dataset.data_.size(); ++i) {
    std::istringstream ss(dataset.data_[i]);
    std::string buf;
    while (ss >> buf) {
      float tf = GetTf(buf, dataset.data_[i]);
      vect_sentence[idfs[buf].first] = tf * idfs[buf].second;
    }
  }
}

void Vectorizer::FillIdfs() {
  std::ifstream file;
  file.open(PATH_TO_IDFS);
  std::string buf;
  if (file.is_open()) {
    while (file) {
      std::getline(file, buf);
      std::istringstream ss(buf);
      int num;
      std::string word;
      float idf;
      ss >> num >> word >> idf;
      std::pair<int, float> p = std::make_pair(num, idf);
      idfs[word] = p;
    }

    file.close();
  }
}

void Vectorizer::CreateIdfsFile() {
  std::ofstream file(PATH_TO_IDFS);
  std::vector<std::string> unique_words = dataset.GetUniqueWords();
  int cnt = 0;
  for (size_t i = 0; i < unique_words.size(); ++i) {
    float idf = GetIdf(unique_words[i]);
    if (!std::isinf(idf)) {
      file << cnt << "\t" << unique_words[i] << "\t" << GetIdf(unique_words[i])
           << std::endl;
      cnt++;
    }
  }
  file.close();
}

float Vectorizer::GetTf(const std::string& word,
                              const std::string& sentence) const {
  std::istringstream ss(sentence);
  std::string buf;
  int num_of_words_in_sentence = 0;
  float res = 0;

  while (ss >> buf) {
    num_of_words_in_sentence += 1;
    if (buf == word) {
      res += 1;
    }
  }

  return res / num_of_words_in_sentence;
}

float Vectorizer::GetIdf(const std::string& word) const {
  float amount_of_docs = dataset.GetAmountOfDocs();
  int amount_of_word_in_docs = dataset.GetAmountOfWordInDocs(word);
  float idf = log(amount_of_docs / amount_of_word_in_docs);
  return idf;
}

std::string Vectorizer::MakeLowercase(std::string sentence) const {
  sentence = CleanSentence(sentence);
  std::transform(sentence.begin(), sentence.end(), sentence.begin(),
    [](unsigned char c){ return std::tolower(c); });
  return sentence;
}

std::string Vectorizer::CleanSentence(std::string sentence) const {
  std::string SPECIAL_SYMBOLS = "!-+=,.@#;:%^&~`()1234567890<>*?/|";
  for (unsigned int i = 0; i < SPECIAL_SYMBOLS.size(); ++i) {
    sentence.erase(std::remove(sentence.begin(), sentence.end(), 
    SPECIAL_SYMBOLS[i]), sentence.end());
  }

  return sentence;
}

std::vector<float> Vectorizer::GetVectorizedSentence 
(const std::string& sentence) const {
  std::vector<float> result(dataset.GetAmountOfUniqueWords(), 0.0);
  auto sentence_buf = MakeLowercase(sentence);
  std::istringstream ss(sentence_buf);
  std::string buf;
  std::vector<std::string> uniques = dataset.GetUniqueWords();

  while (ss >> buf) {
    if (std::find(uniques.begin(), uniques.end(), buf) != uniques.end()) {
      float tf = GetTf(buf, sentence_buf);
      int pos = idfs.at(buf).first;
      if (pos == 0 && buf != dataset.data_[0])
        continue;
      result[pos] = tf * idfs.at(buf).second;
    }
  }
  return result;
}
}  // namespace calmgram::ml::data
