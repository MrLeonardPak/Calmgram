#pragma once
#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "vectorizer.h"
#include "optimizer.h"

namespace calmgram::ml::nn {
    class Classifier {
        std::string method_;
        int n_estimators_;
        std::vector<float> weightss_;
        float learning_rate_;

        public:
        Classifier() {}

        void Fit(/*calmgram::ml::data::Vectorizer x_train, std::vector<int> y_train*/);
        bool Predict(/*calmgram::ml::data::Vectorizer x_test*/);
        std::vector<float> PredictProba(/*calmgram::ml::data::Vectorizer x_test*/);
        ~Classifier() {}
    };
};



#endif
