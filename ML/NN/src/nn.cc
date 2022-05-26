#include "nn.h"

namespace calmgram::ml::nn {
NN::NN() {
  std::ifstream file;
  file.open(PATH_TO_COEFS);
  std::string buf;
  double w;
  if (file.is_open()) {
    while (file) {
      std::getline(file, buf);
      w = ::atof(buf.c_str());
      weights_.push_back(w);
    }
  } 

  file.close();
}

NN::NN(const int& epochs,
       const double& learning_rate)
    : epochs_(epochs), learning_rate_(learning_rate) {
  std::ifstream file;
  file.open(PATH_TO_COEFS);
  std::string buf;
  double w;
  if (file.is_open()) {
    while (file) {
      std::getline(file, buf);
      w = ::atof(buf.c_str());
      weights_.push_back(w);
    }
  } else {
    for (int i = 0; i < dataset_.GetAmountOfUniqueWords(); ++i) {
      weights_.push_back((double)rand() / RAND_MAX);
    }

    std::thread threadForFit([this] { 
      Fit(vect_.GetVectorizedData());
    });

    //threadForFit.join();
    threadForFit.detach();

    CreateCoefsFile();
  }

  file.close();
}

void NN::Fit(std::vector<std::vector<double>> const& X) {
  int epochsCnt = 0;

  while (epochsCnt != epochs_ ) {
    for (size_t i = 0; i <X.size(); ++i) {
      double z = 0;
      for (size_t j = 0; j < X[0].size(); ++j) {
        z += weights_[j] * X[i][j];
      }

      UpdateWeights(X[i], z);
    }

    /*double loss = CalculateBCELoss(dataset_.GetAnswers(), GetHypotheses(X));
    double accuracy = CalculateAccuracy(dataset_.GetAnswers(), GetHypotheses(X));

    std::cout << "Epoch: " << epochsCnt  << " BCELoss: " 
              << loss << " Accuracy: " << accuracy << std::endl;*/

    epochsCnt++;
  }
}

double NN::CalculateAccuracy(const std::vector<int> yTrue, 
              const std::vector<double> yHyposis) const {
  double res = 0;
  for (size_t i = 0; i < yTrue.size(); ++i) {
    int hyp;

    if (yHyposis[i] > 0.5) {
      hyp = 1;
    } else {
      hyp = 0;
    }

    if (yTrue[i] == hyp) {
      res += 1;
    }
  }

  return res / yTrue.size();
}

std::vector<double> NN::GetHypotheses(std::vector<std::vector<double>> const& X) {
  std::vector<double> result;
  for (size_t i = 0; i < X.size(); ++i) {
    double z = 0;
    for (size_t j = 0; j < X[0].size(); ++j) {
      z += weights_[j] * X[i][j];
    }
    result.push_back(GetActivation(z));
  }

  return result;
}

void NN::CreateCoefsFile() {
  std::ofstream file (PATH_TO_COEFS);
  if (file.is_open()) {
    for (const auto & coefficient : weights_) {
      file << coefficient << std::endl;
    }
  }
  file.close();
}

void NN::UpdateWeights( 
                       std::vector<double> vectSentence, double z) {
  std::vector<double> gradient = GetGradient(vectSentence, z);

  if (GetEucledianMetric(gradient) < 0.001) {
    return;
  }

  for (size_t i = 0; i < weights_.size(); ++i) {
    weights_[i] -= learning_rate_ * gradient[i];
  }
}

double NN::GetEucledianMetric(const std::vector<double> gradient) {
  double result = 0;
  for (const auto & element : gradient) {
    result += element;
  }

  return sqrt(result);
}

std::vector<double> NN::GetGradient( 
                      std::vector<double> vectSentence, double z) {
  
  std::vector<double> gradient(vectSentence.size());
  std::vector<int> trueValues = dataset_.GetAnswers();
  for (size_t i = 0; i < gradient.size(); ++i) {
    gradient[i] = GetBCEDerivative(trueValues, vectSentence[i], z);
  }

  return gradient;
}

double NN::GetBCEDerivative(std::vector<int> trueValues, double x, double z) {
  double res = 0;
  double a = 3.0 / (trueValues.size());
  double firstMember = 0;
  double secondMember = 0;
  for (const auto & y: trueValues) {
    
    firstMember += 1.0 * y;
    secondMember += (1.0 * y) / 3;
  }

  res += (firstMember - 2) * exp(2 * z);
  res += (secondMember - 1) * exp(3 * z);

  res += (firstMember - 1) * exp(z);
  res += secondMember;

  res *= x;
  res *= a;

  res /= ((exp(z) + 1) * (exp(z) + 1) * (exp(z) + 1));

  return res;
}

double NN::CalculateBCELoss(const std::vector<int> yTrue, 
          const std::vector<double> yHyposis) const {
  double res = 0;
  for (size_t i = 0; i < yTrue.size(); ++i) {
    res += yTrue[i] * log(yHyposis[i]) + (1 - yTrue[i]) * log(1 - yHyposis[i]);
  }

  return -res / yTrue.size();
}

double NN::GetActivation(double z) const {
  return 1 / (1 + exp(-1 * z));
}

bool NN::AnalysisText(std::string_view const& msg) const {
  
  std::vector<double> vect_sent = vect_.GetVectorizedSentence(msg);
  double z = 0;
  for (int i = 0; i < dataset_.GetAmountOfUniqueWords(); ++i) {
    z += weights_[i] * vect_sent[i];
  }

  double probability = GetActivation(z);
  if (probability > 0.5) {
    return true;
  }

  return false;
}

}  // namespace calmgram::ml::nn
