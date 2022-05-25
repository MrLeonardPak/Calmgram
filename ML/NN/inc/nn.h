#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "vectorizer.h"
#include <thread>
#include "interface_uc_output.h"

#define PATH_TO_COEFS "..ML/files/coefs.txt"

namespace calmgram::ml::nn {

class NN : public IAnalysisText {
  data::Dataset dataset_;
  data::Vectorizer vect_;

  int epochs_ = 10;
  double learning_rate_ = 0.001;
  std::vector<double> weights_;

 public:
  NN();
  NN( const int& epochs,
      const double& learning_rate);

  void Fit();

  /*std::vector<double> GetTfidf(std::string sentence)*/

  bool AnalysisText(std::string_view const& msg) const override;

  void Fit(std::vector<std::vector<double>> const& X);

  void UpdateWeights( 
                     std::vector<double> vectSentence, double z);

  std::vector<double> GetGradient ( 
                     std::vector<double> vectSentence, double z);

  double GetActivation(double z) const;
  double GetBCEDerivative (std::vector<int> trueValues, double x, double z);
  double GetEucledianMetric(const std::vector<double> gradient);
  void CreateCoefsFile();
  double CalculateBCELoss(const std::vector<int> yTrue, const std::vector<double> yHyposis) const;
  std::vector<double> GetHypotheses(std::vector<std::vector<double>> const& X);
  double CalculateAccuracy(const std::vector<int> yTrue, const std::vector<double> yHyposis) const;

  std::vector<double> GetGradient();
};
};  // namespace calmgram::ml::nn

#endif