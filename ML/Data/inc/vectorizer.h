#pragma once
#ifndef VECTORIZER_H
#define VECTORIZER_H

#include "dataset.h"

namespace calmgram::ml::data {
    class Vectorizer {
        std::vector<std::vector<float>> vect_data_;
        calmgram::ml::data::Dataset text_data_;

        public:
        Vectorizer() {}
        Vectorizer(calmgram::ml::data::Dataset text_data_, std::vector<std::vector<float>> vect_data_) {}

        float GetTf(std::string word);
        float GetIdf(std::string word);
        std::vector<std::vector<float>> FitTransorm();
        
        ~Vectorizer() {}
    };
};

#endif VECTORIZER_H

