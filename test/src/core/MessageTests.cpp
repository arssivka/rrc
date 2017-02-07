/**
 *  @autor arssivka
 *  @date 1/11/17
 */
#include "gtest/gtest.h"
#include <rrc/core/Buffer.h>

using namespace rrc;

TEST(MessageTest, Message) {
    constexpr size_t len = 4;
    uint8_t array[len] = {1, 2, 3, 4};
    Buffer message(array, len);
//    EXPECT_EQ(true, true);
}