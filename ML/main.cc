#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <math.h>
#include <cmath>
#include <random>

class Dataset {
    std::vector<std::string> data_;
    std::vector<std::string> unique_words_;

    public:
    friend class Vectorizer;
    friend class NN;

    Dataset() {

        fill_data_();
        fill_unique_words_();

    }

    void fill_data_() {
        std::ifstream file;

        file.open("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/data.txt");
        std::string buf;

        if (file.is_open()) {
            while (file) {
                std::getline(file, buf);
                std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
                if (buf == "" ) {
                    continue;
                }
                data_.push_back(buf);
            }
            file.close();
        }
    }

    void fill_unique_words_() {
        std::ifstream file; 
        file.open("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/vocab.txt");
        std::string buf;
        if (file.is_open()) {
            while (file) {
                std::getline(file, buf);
                std::transform(buf.begin(), buf.end(), buf.begin(), ::tolower);

                if (buf == "" && check_if_word_contains(unique_words_, buf)) {
                    continue;
                }

                unique_words_.push_back(buf);
            }
            file.close();
        }
    }

    bool check_if_word_contains(std::vector<std::string> &v, std::string &word) {
        if(std::find(v.begin(), v.end(), word) != v.end()) {
            return true;
        } else {
            return false;
        }
    }
    
    int get_amount_of_word_in_docs(std::string word) {
        int res = 0;
        std::string buf;

        for (int i = 0; i < data_.size(); ++i) {
            std::istringstream ss(data_[i]);
            while (ss >> buf) {
                if (word == buf) {
                    res += 1;
                    continue;
                }
            }
        }

        return res;
    }

    int get_amount_of_docs() {
        return data_.size();
    }

    std::vector<std::string> get_unique_words() {
        return unique_words_;
    }

    std::vector<std::string> get_data_() {
        return data_;
    }

    int get_amount_of_unique_words() {
        return unique_words_.size();
    }

    ~Dataset() = default;
};

bool check_if_file_exists(std::string filename) {
    std::ifstream f(filename.c_str());
    return f.good();
}

class Vectorizer {
    std::vector<std::vector<float>> vect_data_;
    Dataset dataset;
    std::map<std::string, std::pair<int, float>> idfs;

    public:
    friend class NN;
    Vectorizer(Dataset dataset) : dataset(dataset) {
        if(!check_if_file_exists("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/idfs.txt")) {
            create_idfs_file();
            fill_idfs();
        } else {
            fill_idfs();
        }

        std::vector<float> vect_sentence(dataset.get_amount_of_unique_words(), 0);
        for (int i = 0; i < dataset.data_.size(); ++i) {
            std::istringstream ss(dataset.data_[i]);
            std::string buf;
            while (ss >> buf) {
                float tf = get_tf(buf, dataset.data_[i]);
                vect_sentence[idfs[buf].first] = tf * idfs[buf].second;
            }
        }
    }

    void fill_idfs() {
        std::ifstream file; 
        file.open("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/idfs.txt");
        std::string buf;
        if (file.is_open()) {
            while (file) {
                std::getline(file, buf);
                std::istringstream ss(buf);
                int num;
                std::string word;
                float idf;
                ss >> num >> word >> idf;
                std::pair<int, float> p = std::make_pair(num, idf);
                idfs[word] = p;
            }
            file.close();
        }
    }

    void create_idfs_file() {
        std::ofstream file("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/idfs.txt");
        std::vector<std::string> unique_words = dataset.get_unique_words();
        int cnt = 0;
        for (int i = 0; i < unique_words.size(); ++i) {
            float idf = get_idf(unique_words[i]);
            if (!std::isinf(idf)) {
                file << cnt << "\t" << unique_words[i] << "\t" << get_idf(unique_words[i]) << std::endl;
                cnt++;
            }
        }

        file.close();
    }

    float get_tf(std::string word, std::string sentence) {
        std::istringstream ss(sentence);
        std::string buf;
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

    float get_idf(std::string word) {
        float amount_of_docs = dataset.get_amount_of_docs();
        int amount_of_word_in_docs = dataset.get_amount_of_word_in_docs(word);
        float idf = log(amount_of_docs / amount_of_word_in_docs);

        return idf;
    }

    std::vector<float> get_vectorized_sentence(std::string sentence) {
        std::vector<float> result(dataset.get_amount_of_unique_words(), 0.0);
        std::istringstream ss(sentence);
        std::string buf;

        while (ss >> buf) {
            float tf = get_tf(buf, sentence);
            int pos = idfs[buf].first;
            if (pos == 0 && buf != dataset.data_[0])
                continue;
            result[pos] = tf * idfs[buf].second;
        }

        return result;
    }
    
    ~Vectorizer() = default;
};

class NN {
    Vectorizer vect_;
    Dataset dataset_;
    std::vector<float> weights_;
    int epochs_;
    float learning_rate_;

    public:
    NN(const Vectorizer& vect, const int& epochs = 10, const float& learning_rate = 10) : 
    vect_(vect), 
    epochs_(epochs),
    learning_rate_(learning_rate) {
        std::ifstream file; 
        file.open("C:/Users/user/Desktop/TECHPARK/Algos/dz1/src/coefs.txt");
        std::string buf;
        float w;
        if (file.is_open()) {
            while (file) {
                std::getline(file, buf);
                w = ::atof(buf.c_str());
                weights_.push_back(w);
            }   
        } else {
        for (int i = 0; i < dataset_.get_amount_of_unique_words(); ++i) {
            weights_.push_back((float) rand() / RAND_MAX);
        }
    }
    file.close();
    }

    void fit() {
        for (int i = 0; i < epochs_; ++i) {
            
        }
    }

    /*std::vector<float> get_tfidf(std::string sentence) {
        int vocab_size = dataset_.get_amount_of_unique_words();
        std::vector<float> res(vocab_size, 0);
        for (int i = 0; i < vocab_size; ++i) {
            float tf = vect_.get_tf(dataset_.unique_words_[i], sentence);
            float idf = vect_.idfs[dataset_.unique_words_[i]].second;
            res.push_back(tf * idf);
        }

        return res;
    }*/

    bool predict(std::string sentence) {
        std::vector<float> vect_sent = vect_.get_vectorized_sentence(sentence);
        float z = 0;
        for (int i = 0; i < dataset_.get_amount_of_unique_words(); ++i) {
            z += weights_[i] * vect_sent[i];
        }

        float probability = get_activation(z);
        if (probability > 0.51) {
            return true;
        }
        return false;
    }

    float get_activation(float z) {
        return 1 / (1 + exp(-1 * z));
    }

    std::vector<float> get_grad() {

    }
};

int main() {
    Dataset obj;
    Vectorizer vect(obj);
    NN cl(vect);
    if (cl.predict("привет как дела")) {
        std::cout << "1" << std::endl;
    } else {
        std::cout << "0" << std::endl;
    }
}

