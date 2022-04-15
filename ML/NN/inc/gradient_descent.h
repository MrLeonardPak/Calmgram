#pragma once
#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include "optimizer.h"

namespace calmgram::ml::nn {
    class GradientDescent: calmgram::ml::nn::Optimizer {
        std::vector<float> weights;
        std::vector<float> gradient;

        public:
        GradientDescent();

        void MakeStep(/*float lr_rate, std::vector<float> &gradient*/) override;
        void CountGradient(/*std::vector<float> &gradient*/) override;
        void GetWeights() override;
        float CountLoss(/*std::vector<int> y_true, std::vector<int> y_pred*/) override;
        
        ~GradientDescent();
    };
};

#endif