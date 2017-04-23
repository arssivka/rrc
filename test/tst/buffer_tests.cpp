/**
 *  @autor tekatod
 *  @date 3/16/17
 */

#include <gtest/gtest.h>
#include "rrc/rrc.h"

using namespace rrc;

TEST(shared_buffer, operator_square_brackets) {
    std::string str("catdog");
    string shared_buffer1(str);
    EXPECT_EQ(str[0], shared_buffer1[0]);
    EXPECT_EQ(str[1], shared_buffer1[1]);
    EXPECT_EQ(str[2], shared_buffer1[2]);
    EXPECT_EQ(str[3], shared_buffer1[3]);
    EXPECT_EQ(str[4], shared_buffer1[4]);
    EXPECT_EQ(str[5], shared_buffer1[5]);
}

TEST(shared_buffer, equalty_operators) {
    std::string str("cat");
    std::string str1("cat");
    std::string str2("dog");
    string shared_buffer1(str);
    string shared_buffer2(str1);
    string shared_buffer3(str2);
    EXPECT_EQ(str == str1, shared_buffer1 == shared_buffer2);
    EXPECT_EQ(str == str2, shared_buffer1 == shared_buffer3);
    EXPECT_EQ(str != str1, shared_buffer1 != shared_buffer2);
    EXPECT_EQ(str != str2, shared_buffer1 != shared_buffer3);
    EXPECT_TRUE(shared_buffer1 == str1);
    EXPECT_FALSE(shared_buffer1 == str2);
    EXPECT_TRUE(shared_buffer1 != str2);
    EXPECT_FALSE(shared_buffer1 != str1);
}

TEST(shared_buffer, size) {
    std::string str("ups");
    string shared_buffer1(str);
    EXPECT_EQ(str.size(), shared_buffer1.size());
}


