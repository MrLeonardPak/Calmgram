#pragma once
#ifndef DATASET_H
#define DATASET_H

#include <math.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <cassert>

#define PATH_TO_DATA "ML/files/data.txt"
#define PATH_TO_VOCAB "ML/files/vocab.txt"
#define PATH_TO_IDFS "ML/files/idfs.txt"

bool CheckIfFileExists(std::string filename) {
  std::ifstream f(filename.c_str());
  return f.good();
}


namespace calmgram::ml::data {
  template <typename MsgType>
    class Dataset {
        std::vector<MsgType> data_;
        std::vector<MsgType> unique_words_;

        public:
        friend class Vectorizer;
        friend class NN;

        Dataset();
        void FillData();
        void FillUniqueWords();
        bool CheckIfWordContains(const std::vector<MsgType>& v, const MsgType& word) const;
        const int GetAmountOfWordInDocs(const MsgType& word) const;
        const int GetAmountOfDocs() const;
        const std::vector<MsgType> GetUniqueWords() const;
        const std::vector<MsgType> GetData() const;
        const int GetAmountOfUniqueWords() const;
        ~Dataset() = default;
    };
};

#endif