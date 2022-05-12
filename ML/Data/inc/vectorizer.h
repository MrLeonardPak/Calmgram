#pragma once
#ifndef VECTORIZER_H
#define VECTORIZER_H

#include "dataset.h"

namespace calmgram::ml::data {
    template <typename MsgType>
    class Vectorizer {
        std::vector<std::vector<float>> vect_data_;
        Dataset<MsgType> dataset;
        std::map<MsgType, std::pair<int, float>> idfs;

        public:
        friend class NN;
        Vectorizer();
        void FillIdfs();
        void CreateIdfsFile();
        const float GetTf(const MsgType& word, const MsgType& sentence) const;
        const float GetIdf(const MsgType& word) const;
        std::vector<float> GetVectorizedSentence(const MsgType& sentence) const;
        ~Vectorizer() = default;
    };
}

#endif

