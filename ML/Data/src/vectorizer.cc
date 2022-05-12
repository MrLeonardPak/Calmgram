#include "vectorizer.h"

namespace calmgram::ml::data {
    template <typename MsgType>
    Vectorizer<MsgType>::Vectorizer() {
        if (!CheckIfFileExists(PATH_TO_IDFS)) {
            CreateIdfsFile();
            FillIdfs();
        } else {
            FillIdfs();
        }

        std::vector<float> vect_sentence(dataset.GetAmountOfUniqueWords(), 0);
        for (int i = 0; i < dataset.data_.size(); ++i) {
            std::istringstream ss(dataset.data_[i]);
            MsgType buf;
            while (ss >> buf) {
                float tf = GetTf(buf, dataset.data_[i]);
                vect_sentence[idfs[buf].first] = tf * idfs[buf].second;
            }   
        }
    }

    template <typename MsgType>
    void Vectorizer<MsgType>::FillIdfs() {
        std::ifstream file;
        file.open(PATH_TO_IDFS);
        MsgTy buf;
        if (file.is_open()) {
            while (file) {
                std::getline(file, buf);
                std::istringstream ss(buf);
                int num;
                MsgType word;
                float idf;
                ss >> num >> word >> idf;
                std::pair<int, float> p = std::make_pair(num, idf);
                idfs[word] = p;
            }

            file.close();
        }
    }

    template <typename MsgType>
    void Vectorizer<MsgType>::CreateIdfsFile() {
        std::ofstream file(PATH_TO_IDFS);
        std::vector<MsgType> unique_words = dataset.GetUniqueWords();
        int cnt = 0;
        for (int i = 0; i < unique_words.size(); ++i) {
            float idf = GetIdf(unique_words[i]);
            if (!std::isinf(idf)) {
                file << cnt << "\t" << unique_words[i] << "\t"
                    << GetIdf(unique_words[i]) << std::endl;
                cnt++;
            }
        }
        file.close();
    }

    template <typename MsgType>
    const float Vectorizer<MsgType>::GetTf(const MsgType& word, const MsgType& sentence) const {
        std::istringstream ss(sentence);
        MsgType buf;
        int num_of_words_in_sentence = 0;
        float res = 0;

        while (ss >> buf) {
            num_of_words_in_sentence += 1;
            if (buf == word) {
                res += 1;
            }
        }

        return res / num_of_words_in_sentence;
    }

    template <typename MsgType>
    const float Vectorizer<MsgType>::GetIdf(const MsgType& word) const {
        float amount_of_docs = dataset.GetAmountOfDocs();
        int amount_of_word_in_docs = dataset.GetAmountOfWordInDocs(word);
        float idf = log(amount_of_docs / amount_of_word_in_docs);
        return idf;
  }

    template <typename MsgType>
    std::vector<float> Vectorizer<MsgType>::GetVectorizedSentence(const MsgType& sentence) const {
        std::vector<float> result(dataset.GetAmountOfUniqueWords(), 0.0);
        std::istringstream ss(sentence);
        MsgType buf;
        std::vector<MsgType> uniques = dataset.GetUniqueWords();

        while (ss >> buf) {
            if (std::find(uniques.begin(), uniques.end(), buf) != uniques.end()) {
                float tf = GetTf(buf, sentence);
                int pos = idfs.at(buf).first;
                if (pos == 0 && buf != dataset.data_[0])
                    continue;
                result[pos] = tf * idfs.at(buf).second;
            }
        }
        return result;
    }
}

