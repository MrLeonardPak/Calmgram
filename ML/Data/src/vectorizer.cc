#include "vectorizer.h"

namespace calmgram::ml::data {
    float Vectorizer::GetTf ( /*std::string word*/ ) {
        int a = text_data_.GetAmountOfUniqueWords(); // Mock
        return a;
    }

    float Vectorizer::GetIdf ( /*std::string word*/ ) {
        int a = text_data_.GetAmountOfWordInDoc(); // Mock
        return a;
    }

    std::vector<std::vector<float>> Vectorizer::FitTransorm() {
        std::vector<std::vector<float>> ret = {{0.1}};
        return ret;
    }
}

