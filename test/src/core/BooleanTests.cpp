/**
 *  @autor tekatod
 *  @date 2/15/17
 */

#include <iostream>
#include <gtest/gtest.h>
#include <rrc/core/Boolean.h>

using namespace rrc;

TEST(BooleanTests, DefaultConstructorValueTest) {
    Boolean boolean;
    EXPECT_FALSE(boolean.get());
}

TEST(BooleanTests, NonDefaultConstructorSetGetTest) {
    Boolean boolean(true);
    EXPECT_TRUE(boolean.get());
    boolean.set(false);
    EXPECT_FALSE(boolean.get());
}

TEST(BooleanTests, EqualityOperatorsTests) {
    Boolean boolean(true);
    Boolean boolean1(false);
    EXPECT_FALSE(boolean == boolean1);
    EXPECT_TRUE(boolean != boolean1);
    boolean1.set(true);
    EXPECT_FALSE(boolean != boolean1);
    EXPECT_TRUE(boolean == boolean1);
}

TEST(BooleanTests, CopyMoveConstructorTests) {
    Boolean boolean;
    Boolean boolean1(boolean);
    EXPECT_FALSE(boolean1.get());
    Boolean boolean2(Boolean(true));
    EXPECT_TRUE(boolean2.get());
}

TEST(BooleanTests, AssigmentOperatorTests) {
    Boolean boolean(false);
    Boolean boolean1 = boolean;
    EXPECT_FALSE(boolean1.get());
    Boolean boolean2 = Boolean(true);
    EXPECT_TRUE(boolean2.get());
}