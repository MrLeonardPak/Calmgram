#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "vectorizer.h"
#include "interface_uc_output.h"

#define PATH_TO_COEFS "../ML/files/coefs.txt"

namespace calmgram::ml::nn {

class NN : public IAnalysisText {
  data::Dataset dataset_;
  data::Vectorizer vect_;

  std::vector<float> weights_;
  int epochs_ = 10;
  float learning_rate_ = 10;

 public:
  NN();
  NN(const calmgram::ml::data::Vectorizer& vect,
      const int& epochs,
      const float& learning_rate);

  void Fit();

  /*std::vector<float> GetTfidf(std::string sentence)*/

  bool AnalysisText(std::string const& msg) const override;

  float GetActivation(float z) const;

  std::vector<float> GetGradient();
};
};  // namespace calmgram::ml::nn

#endif
