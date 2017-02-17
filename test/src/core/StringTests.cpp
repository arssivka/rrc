/**
 *  @autor tekatod
 *  @date 2/15/17
 */

#include <iostream>
#include <gtest/gtest.h>
#include <rrc/core/String.h>

using namespace rrc;

TEST(StringTests, DefaultConstructorTests) {
    String string;
    EXPECT_TRUE(string.isEmpty());
}

TEST(StringTests, NonDefaultConstructorSetGetTest) {
    String string("42");
    EXPECT_FALSE(string.isEmpty());
    EXPECT_EQ(string.get(), std::string("42"));
    EXPECT_EQ(string.getSize(), (size_t) 2);
    string.set("142");
    EXPECT_EQ(string.get(), std::string("142"));
    EXPECT_EQ(string.getSize(), (size_t) 3);
    String string1(5, '3');
    EXPECT_EQ(string1.get(), std::string("33333"));
    String string2{'x', 'y', 'z'};
    EXPECT_EQ(string2.get(), std::string("xyz"));
    std::string stdString("424242");
    String string3(stdString, 2, 4);
    EXPECT_EQ(string3.get(), std::string("4242"));
    String string4(stdString.begin(), stdString.end());
    EXPECT_EQ(string4.get(), stdString);
}

TEST(StringTests, EqualityOperatorsTests) {
    String string("42");
    String string1("24");
    EXPECT_FALSE(string == string1);
    EXPECT_TRUE(string != string1);
    string1.set("42");
    EXPECT_FALSE(string != string1);
    EXPECT_TRUE(string == string1);
}

TEST(StringTests, CopyMoveConstructorTests) {
    std::string stdString("42");
    String string(stdString);
    EXPECT_EQ(string.get(), std::string("42"));
    String string1(std::string("42"));
    EXPECT_EQ(string1.get(), std::string("42"));
    String string2(string1);
    EXPECT_EQ(string2.get(), std::string("42"));
    String string3(String("42"));
    EXPECT_EQ(string3.get(), std::string("42"));
}

TEST(StringTests, AssigmentOperatorTests) {
    String string("42");
    String string1 = string;
    EXPECT_EQ(string, string1);
    String string2 = String("42");
    EXPECT_EQ(string2, string1);
}

TEST(StringTests, SquareBracketsTests) {
    String string("012");
    EXPECT_EQ(string[0], '0');
    EXPECT_EQ(string[1], '1');
    EXPECT_EQ(string[2], '2');
}

TEST(StringTests, IteratorsTests) {
    String string("012");
    uint8_t check = 0;
    for(auto it = string.begin(); it != string.end(); ++it) {
        check++;
    }
    EXPECT_EQ(check, string.getSize());
    std::vector<char> checkVector{'2', '1', '0'};
    std::vector<char> fillVector;
    for(auto it = string.rbegin(); it != string.rend(); ++it) {
        fillVector.push_back(*it);
    }
    EXPECT_EQ(checkVector, fillVector);
}

TEST(StringTests, CompareOperatorsTests) {
    String string("42");
    String string1("abc");
    std::string stdString1("42");
    std::string stdString2("abc");
    EXPECT_EQ(string < string1, stdString1 < stdString2);
    EXPECT_EQ(string > string1, stdString1 > stdString2);
    EXPECT_EQ(string <= string1, stdString1 <= stdString2);
    EXPECT_EQ(string >= string1, stdString1 >= stdString2);
}
