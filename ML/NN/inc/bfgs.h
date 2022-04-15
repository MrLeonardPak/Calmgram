#pragma once
#ifndef BFGS_H
#define BFGS_H

#include "optimizer.h"

namespace calmgram::ml::nn {
    class BFGS: calmgram::ml::nn::Optimizer {
        std::vector<float> weights;
        std::vector<float> gradient;

        public:
        BFGS();

        void MakeStep(/*float lr_rate, std::vector<float> &gradient*/) override;
        void CountGradient(/*std::vector<float> &gradient*/) override;
        void GetWeights() override;
        float CountLoss(/*std::vector<int> y_true, std::vector<int> y_pred*/) override;

        ~BFGS();
    };
};

#endif