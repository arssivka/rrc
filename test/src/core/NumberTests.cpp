/**
 *  @autor tekatod
 *  @date 2/15/17
 */

#include <gtest/gtest.h>
#include <rrc/core/Number.h>

using namespace rrc;

TEST(NumberTests, DefaultConstructorValueTest) {
    Number number;
    EXPECT_EQ(number.get(), (double) 0.0);
}

TEST(NumberTests, NonDefaultConstructorSetGetTest) {
    Number number(42.0);
    EXPECT_EQ(number.get(), (double) 42.0);
}

TEST(NumberTests, EqualityOperatorsTests) {
    Number number(42.0);
    Number number1(24.0);
    EXPECT_FALSE(number == number1);
    EXPECT_TRUE(number != number1);
    number1.set(42.0);
    EXPECT_FALSE(number != number1);
    EXPECT_TRUE(number == number1);
}

TEST(NumberTests, CopyMoveConstructorTests) {
    Number number(42.0);
    Number number1(number);
    EXPECT_EQ(number1.get(), (double) 42.0);
    Number number2(Number(42.0));
    EXPECT_EQ(number2.get(), (double) 42.0);
}

TEST(NumberTests, AssigmentOperatorTests) {
    Number number(42.0);
    Number number1 = number;
    EXPECT_EQ(number1.get(), (double) 42.0);
    Number number2= Number(42.0);
    EXPECT_EQ(number2.get(), (double) 42.0);
}

TEST(NumberTests, CimpareOperatorsTests) {
    Number number(42.0);
    Number number1(42.0);
    Number number2(24.0);
    EXPECT_TRUE(number1 > number2);
    EXPECT_TRUE(number1 >= number2);
    EXPECT_FALSE(number1 <= number2);
    EXPECT_FALSE(number1 < number2);
    EXPECT_TRUE(number1 <= number);
    EXPECT_TRUE(number1 >= number);
}