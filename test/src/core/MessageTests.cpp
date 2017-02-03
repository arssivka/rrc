/**
 *  @autor tekatod
 *  @date 1/11/17
 */
#include "gtest/gtest.h"
#include <rrc/core/Message.h>

using namespace rrc;


TEST(MessageTest, GetVectorTest) {
    uint8_t buf[] = {1, 0, 1, 0, 1};
    Message testMessage(buf, 5);
    auto vec = testMessage.getBinaryVector();
    std::vector<uint8_t> testVec{1, 0, 1, 0, 1};
    EXPECT_EQ(testVec, vec);
}

TEST(MessageTest, EmptyTest) {
    uint8_t buf[] = {1, 0, 1, 0, 1};
    Message testMessage(buf, 0);
    EXPECT_TRUE(testMessage.isEmpty());
    Message testMessage1(buf, 5);
    EXPECT_FALSE(testMessage1.isEmpty());
}