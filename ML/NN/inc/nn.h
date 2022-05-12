#pragma once
#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "vectorizer.h"
#include "interfaces_use_case.h"

#define PATH_TO_COEFS "ML/files/coefs.txt"

namespace calmgram::ml::nn {
    template <typename MsgType>
    class NN : public calmgram::api_server::use_case::IAnalysisText {
        calmgram::ml::data::Dataset<MsgType> dataset_;
        calmgram::ml::data::Vectorizer<MsgType> vect_;

        std::vector<float> weights_;
        int epochs_;
        float learning_rate_;

        public:
        NN();
        NN(const calmgram::ml::data::Vectorizer<MsgType> &vect, const int& epochs = 10, 
        const float& learning_rate = 10);

        void Fit();

        /*std::vector<float> GetTfidf(MsgType sentence)*/

        bool AnalysisText(MsgType const& msg) const override;

        const float GetActivation(float z) const;

        std::vector<float> GetGradient();
    };
};



#endif
