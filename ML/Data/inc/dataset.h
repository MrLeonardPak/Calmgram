#pragma once
#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <vector>
#include <string.h>

namespace calmgram::ml::data {
    class Dataset {
        std::vector<std::vector<std::string>> data_;
        int NumOfDocs_;
        std::vector<std::string> uniqueWords_;
        public:

        Dataset() {}
        Dataset(std::vector<std::vector<std::string>> data) {
            data_ = data;
            // to be continued ...
        }
        
        std::vector<std::vector<std::string>> GetHead( /*int amount = 5*/ );
        int GetAmountOfWordInDoc( /*std::string word*/ );
        int GetAmountOfUniqueWords();
        ~Dataset() {}
    };
};

#endif