#include "nn.h"

namespace calmgram::ml::nn {
NN::NN() {
  std::ifstream file;
  file.open(PATH_TO_COEFS);
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

NN::NN(const calmgram::ml::data::Vectorizer& vect,
       const int& epochs = 10,
       const float& learning_rate = 10)
    : vect_(vect), epochs_(epochs), learning_rate_(learning_rate) {
  std::ifstream file;
  file.open(PATH_TO_COEFS);
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

/*std::vector<float> NN::get_tfidf(std::string sentence) {
    int vocab_size = dataset_.GetAmountOfUniqueWords();
    std::vector<float> res(vocab_size, 0);
    for (int i = 0; i < vocab_size; ++i) {
        float tf = vect_.GetTf(dataset_.unique_words_[i], sentence);
        float idf = vect_.idfs[dataset_.unique_words_[i]].second;
        res.push_back(tf * idf);
    }

    return res;
}*/

float NN::GetActivation(float z) const {
  return 1 / (1 + exp(-1 * z));
}

bool NN::AnalysisText(std::string const& msg) const {
  std::vector<float> vect_sent = vect_.GetVectorizedSentence(msg);
  float z = 0;
  for (int i = 0; i < dataset_.GetAmountOfUniqueWords(); ++i) {
    z += weights_[i] * vect_sent[i];
  }

  float probability = GetActivation(z);
  if (probability > 0.5) {
    return true;
  }

  return false;
}

}  // namespace calmgram::ml::nn
