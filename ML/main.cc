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

class IAnalysisText {
 public:
  virtual ~IAnalysisText() = default;
  virtual bool AnalysisText(std::string const& msg) const = 0;
};

class Dataset {
  std::vector<std::string> data_;
  std::vector<std::string> unique_words_;

 public:
  friend class Vectorizer;
  friend class NN;

  Dataset() {
    fill_data_();
    fill_unique_words_();
  }

  void fill_data_() {
    std::ifstream file;

    file.open("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/data.txt");
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

  void fill_unique_words_() {
    std::ifstream file;
    file.open("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/vocab.txt");
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

  bool CheckIfWordContains(std::vector<std::string>& v, std::string& word) {
    if (std::find(v.begin(), v.end(), word) != v.end()) {
      return true;
    } else {
      return false;
    }
  }

  const int GetAmountOfWordInDocs(std::string word) const {
    int res = 0;
    std::string buf;

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

  const int GetAmountOfDocs() const { return data_.size(); }

  const std::vector<std::string> GetUniqueWords() const { return unique_words_; }

  const std::vector<std::string> GetData() const { return data_; }

  const int GetAmountOfUniqueWords() const { return unique_words_.size(); }

  ~Dataset() = default;
};

bool CheckIfFileExists(std::string filename) {
  std::ifstream f(filename.c_str());
  return f.good();
}

class Vectorizer {
  std::vector<std::vector<float>> vect_data_;
  Dataset dataset;
  std::map<std::string, std::pair<int, float>> idfs;

 public:
  friend class NN;
  Vectorizer() {
    if (!CheckIfFileExists("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/idfs.txt")) {
      CreateIdfsFile();
      FillIdfs();
    } else {
      FillIdfs();
    }

    std::vector<float> vect_sentence(dataset.GetAmountOfUniqueWords(), 0);
    for (int i = 0; i < dataset.data_.size(); ++i) {
      std::istringstream ss(dataset.data_[i]);
      std::string buf;
      while (ss >> buf) {
        float tf = GetTf(buf, dataset.data_[i]);
        vect_sentence[idfs[buf].first] = tf * idfs[buf].second;
      }
    }
  }

  void FillIdfs() {
    std::ifstream file;
    file.open("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/idfs.txt");
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

  void CreateIdfsFile() {
    std::ofstream file("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/idfs.txt");
    std::vector<std::string> unique_words = dataset.GetUniqueWords();
    int cnt = 0;
    for (int i = 0; i < unique_words.size(); ++i) {
      float idf = GetIdf(unique_words[i]);
      if (!std::isinf(idf)) {
        file << cnt << "\t" << unique_words[i] << "\t"
             << GetIdf(unique_words[i]) << std::endl;
        cnt++;
      }
    }

    file.close();
  }

  const float GetTf(std::string word, std::string sentence) const {
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

  const float GetIdf(std::string word) const {
    float amount_of_docs = dataset.GetAmountOfDocs();
    int amount_of_word_in_docs = dataset.GetAmountOfWordInDocs(word);
    float idf = log(amount_of_docs / amount_of_word_in_docs);

    return idf;
  }


    std::vector<float> GetVectorizedSentence(const std::string sentence) const {
        std::vector<float> result(dataset.GetAmountOfUniqueWords(), 0.0);
        std::istringstream ss(sentence);
        std::string buf;
        std::vector<std::string> uniques = dataset.GetUniqueWords();

        while (ss >> buf) {
            if (std::find(uniques.begin(), uniques.end(), buf) != uniques.end()) {
                float tf = GetTf(buf, sentence);
                int pos = idfs.at(buf).first;
                if (pos == 0 && buf != dataset.data_[0])
                    continue;
                result[pos] = tf * idfs.at(buf).second;
            }
        }
        return result;
    }

  ~Vectorizer() = default;
};

class NN : public IAnalysisText {
  Dataset dataset_;
  Vectorizer vect_;

  std::vector<float> weights_;
  int epochs_;
  float learning_rate_;

 public:
  NN() {
    std::ifstream file;
    file.open("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/coefs.txt");
    std::string buf;
    float w;
    if (file.is_open()) {
      while (file) {
        std::getline(file, buf);
        w = ::atof(buf.c_str());
        weights_.push_back(w);
      }
    } else {
      for (int i = 0; i < dataset_.GetAmountOfUniqueWords(); ++i) {
        weights_.push_back((float)rand() / RAND_MAX);
      }
    }
    file.close();
  }

  NN(const Vectorizer& vect,
     const int& epochs = 10,
     const float& learning_rate = 10)
      : vect_(vect), epochs_(epochs), learning_rate_(learning_rate) {
    std::ifstream file;
    file.open("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/coefs.txt");
    std::string buf;
    float w;
    if (file.is_open()) {
      while (file) {
        std::getline(file, buf);
        w = ::atof(buf.c_str());
        weights_.push_back(w);
      }
    } else {
      for (int i = 0; i < dataset_.GetAmountOfUniqueWords(); ++i) {
        weights_.push_back((float)rand() / RAND_MAX);
      }
    }
    file.close();
  }

  void Fit() {
    for (int i = 0; i < epochs_; ++i) {
    }
  }

  /*std::vector<float> get_tfidf(std::string sentence) {
      int vocab_size = dataset_.GetAmountOfUniqueWords();
      std::vector<float> res(vocab_size, 0);
      for (int i = 0; i < vocab_size; ++i) {
          float tf = vect_.GetTf(dataset_.unique_words_[i], sentence);
          float idf = vect_.idfs[dataset_.unique_words_[i]].second;
          res.push_back(tf * idf);
      }

      return res;
  }*/

  bool AnalysisText(std::string const& msg) const override {
    std::vector<float> vect_sent = vect_.GetVectorizedSentence(msg);
    float z = 0;
    for (int i = 0; i < dataset_.GetAmountOfUniqueWords(); ++i) {
      z += weights_[i] * vect_sent[i];
    }

    float probability = GetActivation(z);
    if (probability > 0.502) {
      return true;
    }
    return false;
  }

  const float GetActivation(float z) const { return 1 / (1 + exp(-1 * z)); }

  std::vector<float> GetGradient() {}
};

#include <memory>

bool Run(std::shared_ptr<IAnalysisText const> interface,
         std::string const& str) {
  return interface->AnalysisText(str);
}

void Tests() {
  {
    std::string str = "привет как дела";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == false);
  }
  {
    std::string str = "слышал последние новости о путине";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == true);
  }
  {
    std::string str = "предлагаю сходить в хороший бар";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == false);
  }
  {
    std::string str = "россия и украина должна жить в мире";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == true);
  }
  /*{
    std::string str = "лучше гор могут быть только горы";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == false);
  }*/
  /*{
    std::string str = "что ты можешь сказать об афганской войне";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == true);
  }*/
  {
    std::string str = "хочу на рыбалку но жена меня не пускает";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == false);
  }
  {
    std::string str = "завтра будут политические дебаты про украину предлагаю посмотреть"; 
    auto analyser = std::make_shared<NN>(); 
    assert(Run(analyser, str) == true);
  }

  std::cout << "Tests SUCCESS!" << '\n';
}

int main() {
    Tests();
}
