/**
 *  @autor tekatod
 *  @date 2/16/17
 */

#include <gtest/gtest.h>
#include <rrc/core/Nil.h>

using namespace rrc;

TEST(NilTests, CreationTests) {
    EXPECT_NO_THROW(Nil());
}

TEST(NilTests, OperatorsTests) {
    Nil nil;
    Nil nil1;
    EXPECT_FALSE(nil == nil1);
    EXPECT_FALSE(nil != nil1);
    EXPECT_FALSE(nil >= nil1);
    EXPECT_FALSE(nil <= nil1);
    EXPECT_FALSE(nil < nil1);
    EXPECT_FALSE(nil > nil1);
}