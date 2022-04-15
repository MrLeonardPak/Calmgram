#pragma once
#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "classifier.h"

namespace calmgram::ml::nn {
    class Optimizer {
        public:
        Optimizer();

        virtual void MakeStep(float lr_rate, std::vector<float> &gradient) = 0;
        virtual void CountGradient(std::vector<float> &gradient) = 0;
        virtual void GetWeights() = 0;
        virtual float CountLoss(std::vector<int> y_true, std::vector<int> y_pred) = 0;
        
        ~Optimizer();
    };
};

#endif OPTIMIZER_H

