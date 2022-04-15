#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "dataset.h"
#include "vectorizer.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;


class MockDataset: public calmgram::ml::data::Dataset {
    public:
    MOCK_METHOD1(GetAmountOfUniqueWords, int);
    MOCK_METHOD1(GetAmountOfWordInDoc, int);
};

TEST(DatasetTest, AmountOfWords) {
    MockDataset mockdataset;
    EXPECT_CALL(mockdataset, GetAmountOfUniqueWords()).Times(AtLeast(1));
    EXPECT_CALL(mockdataset, GetAmountOfWordInDoc()).Times(AtLeast(1));

    calmgram::ml::data::Vectorizer vect;
    EXPECT_EQ(vect.GetIdf(), 1);
    EXPECT_EQ(vect.GetTf(), 1);
} 
