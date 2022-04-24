#include "dataset.h"

namespace calmgram::ml::data {
    std::vector<std::vector<std::string>> Dataset::GetHead( /*int amount = 5*/ ) {
        std::vector<std::vector<std::string>> ret = {{"ok"}};
        return ret;
    }

    int Dataset::GetAmountOfWordInDoc( /*std::string word*/ ) {
        return 1;
    }

    int Dataset::GetAmountOfUniqueWords() {
        return 1;
    }
}

