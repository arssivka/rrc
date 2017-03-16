/**
 *  @autor tekatod
 *  @date 3/16/17
 */

#include <gtest/gtest.h>
#include "rrc/rrc.h"

using namespace rrc;

TEST(shared_buffer, operator_square_brackets) {
    std::string string("catdog");
    shared_buffer shared_buffer1(string);
    EXPECT_EQ(string[0], shared_buffer1[0]);
    EXPECT_EQ(string[1], shared_buffer1[1]);
    EXPECT_EQ(string[2], shared_buffer1[2]);
    EXPECT_EQ(string[3], shared_buffer1[3]);
    EXPECT_EQ(string[4], shared_buffer1[4]);
    EXPECT_EQ(string[5], shared_buffer1[5]);
}

TEST(shared_buffer, equalty_operators) {
    std::string string("cat");
    std::string string1("cat");
    std::string string2("dog");
    shared_buffer shared_buffer1(string);
    shared_buffer shared_buffer2(string1);
    shared_buffer shared_buffer3(string2);
    EXPECT_EQ(string == string1, shared_buffer1 == shared_buffer2);
    EXPECT_EQ(string == string2, shared_buffer1 == shared_buffer3);
    EXPECT_EQ(string != string1, shared_buffer1 != shared_buffer2);
    EXPECT_EQ(string != string2, shared_buffer1 != shared_buffer3);
    EXPECT_TRUE(shared_buffer1 == string1);
    EXPECT_FALSE(shared_buffer1 == string2);
    EXPECT_TRUE(shared_buffer1 != string2);
    EXPECT_FALSE(shared_buffer1 != string1);
}

TEST(shared_buffer, fill) {
    std::string string("AAAAA");
    shared_buffer shared_buffer1(5);
    shared_buffer1.fill('A');
    EXPECT_TRUE(shared_buffer1 == string);
}

TEST(shared_buffer, size) {
    std::string string("ups");
    shared_buffer shared_buffer1(string);
    EXPECT_EQ(string.size(), shared_buffer1.size());
}


