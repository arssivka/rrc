/**
 *  @autor tekatod
 *  @date 1/25/17
 */

#include "gtest/gtest.h"
#include <rrc/core/ArrayReference.h>
#include "gmock/gmock.h"

using namespace rrc;

TEST(ArrayReferenceTests, EmptyTest) {
    ArrayReference<int> arrayReference;
    EXPECT_FALSE(arrayReference.isInitialized());
    EXPECT_EQ(arrayReference.getSize(), (size_t)0);
}

TEST(ArrayReferenceTests, EqTest) {
    int x[5] = {0, 1, 2, 3, 4};
    ArrayReference<int> arrayReference{x, (size_t) 5};
    EXPECT_EQ(arrayReference.getSize(), (size_t) 5);
    EXPECT_TRUE(arrayReference == x);
    EXPECT_TRUE(arrayReference.isInitialized());
}

TEST(ArrayReferenceTests, GetPointerTest) {
    int x[5] = {0, 1, 2, 3, 4};
    ArrayReference<int> arrayReference{x, (size_t) 5};
    EXPECT_EQ(arrayReference.getArrayPointer(), &x[0]);
}

TEST(ArrayReferenceTests, IteratorsTest) {
    int x[5] = {0, 1, 2, 3, 4};
    ArrayReference<int> arrayReference{x, (size_t) 5};
    int check = 0;
    int sum = 0;
    for(auto it = arrayReference.begin(); it != arrayReference.end(); ++it) {
        check++;
    }
    EXPECT_EQ(check, 5);
    for(auto item : arrayReference) {
        check++;
        sum += item;
    }
    EXPECT_EQ(check, 10);
    EXPECT_EQ(sum, 10);
    std::vector<int> checkVector{4, 3, 2, 1, 0};
    std::vector<int> fillVector;
    for(auto it = arrayReference.rbegin(); it != arrayReference.rend(); ++it) {
        fillVector.push_back(*it);
    }
    EXPECT_EQ(checkVector, fillVector);
}