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

  std::vector<double> vect_sentence(dataset.GetAmountOfUniqueWords(), 0);
  for (size_t i = 0; i < dataset.data_.size(); ++i) {
    std::istringstream ss(dataset.data_[i]);
    std::string buf;
    while (ss >> buf) {
      double tf = GetTf(buf, dataset.data_[i]);
      vect_sentence[idfs[buf].first] = tf * idfs[buf].second;
    }
    vect_data_.push_back(NormalizeSentence(vect_sentence));
  }
}

std::vector<double> Vectorizer::NormalizeSentence(
    std::vector<double> vectSentence) {
  double sum = 0;

  for (const auto& el : vectSentence) {
    sum += el * el;
  }

  for (uint i = 0; i < vectSentence.size(); ++i) {
    vectSentence[i] /= sqrtf(sum);
  }

  return vectSentence;
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
      double idf;
      ss >> num >> word >> idf;
      std::pair<int, double> p = std::make_pair(num, idf);
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
    double idf = GetIdf(unique_words[i]);
    if (!std::isinf(idf)) {
      file << cnt << "\t" << unique_words[i] << "\t" << idf << std::endl;
      cnt++;
    }
  }
  file.close();
}

double Vectorizer::GetTf(const std::string& word,
                         const std::string& sentence) const {
  std::istringstream ss(sentence);
  std::string buf;
  int num_of_words_in_sentence = 0;
  double res = 0;

  while (ss >> buf) {
    num_of_words_in_sentence += 1;
    if (buf == word) {
      res += 1;
    }
  }

  return res / num_of_words_in_sentence;
}

double Vectorizer::GetIdf(const std::string& word) const {
  double amount_of_docs = dataset.GetAmountOfDocs();
  int amount_of_word_in_docs = dataset.GetAmountOfWordInDocs(word);
  double idf = log2((1 + amount_of_docs) / (1 + amount_of_word_in_docs) + 1);
  return idf;
}

std::string Vectorizer::MakeLowercase(std::string sentence) const {
  sentence = CleanSentence(sentence);
  std::transform(sentence.begin(), sentence.end(), sentence.begin(),
                 [](unsigned char c) {
                   // return MyToLower(c);
                   return std::tolower(c);
                 });
  return RusToLower(sentence);
}

std::string Vectorizer::RusToLower(std::string const& str) const {
  std::string res;
  for (size_t i = 0; i < str.size(); i += 2) {
    if (str[i] == -48 && str[i + 1] < -80 && -113 < str[i + 1]) {
      if (-97 < str[i + 1]) {
        res.push_back(-47);
        res.push_back(str[i + 1] - 32);
      } else {
        res.push_back(-48);
        res.push_back(str[i + 1] + 32);
      }
    } else if (str[i + 1] == -127) {
      res.push_back(-47);
      res.push_back(-111);
    } else {
      res.push_back(str[i]);
      res.push_back(str[i + 1]);
    }
  }
  return res;
}

std::string Vectorizer::CleanSentence(std::string sentence) const {
  std::string SPECIAL_SYMBOLS = "!-+=,.@#;:%^&~`()1234567890<>*?/|";
  for (unsigned int i = 0; i < SPECIAL_SYMBOLS.size(); ++i) {
    sentence.erase(
        std::remove(sentence.begin(), sentence.end(), SPECIAL_SYMBOLS[i]),
        sentence.end());
  }

  return sentence;
}

std::vector<double> Vectorizer::GetVectorizedSentence(
    const std::string& sentence) const {
  std::vector<double> result(dataset.GetAmountOfUniqueWords(), 0.0);
  auto sentence_buf = MakeLowercase(sentence);

  std::istringstream ss(sentence_buf);
  std::string buf;
  std::vector<std::string> uniques = dataset.GetUniqueWords();

  while (ss >> buf) {
    if (std::find(uniques.begin(), uniques.end(), buf) != uniques.end()) {
      double tf = GetTf(buf, sentence_buf);
      int pos = idfs.at(buf).first;
      if (pos == 0 && buf != dataset.data_[0])
        continue;
      result[pos] = tf * idfs.at(buf).second;
    }
  }
  return result;
}

const std::vector<std::vector<double>> Vectorizer::GetVectorizedData() const {
  return vect_data_;
}

}  // namespace calmgram::ml::data
