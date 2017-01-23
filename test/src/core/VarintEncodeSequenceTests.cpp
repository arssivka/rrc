/**
 *  @autor tekatod
 *  @date 1/23/17
 */

#include <rrc/meta/VarintEncodeSequence.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace rrc::meta;

TEST(MetaVarintEncodeSequenceTests, EncodeTest1) {
    typedef VarintEncodeSequence<size_t, 150> encoded;
    bool eq = std::is_same<IntegralSequence<uint8_t, 150, 1>, encoded>::value;
    EXPECT_TRUE(eq);
}

TEST(MetaVarintEncodeSequenceTests, EncodeTest2) {
    typedef VarintEncodeSequence<size_t> encoded;
    bool eq = std::is_same<IntegralSequence<uint8_t>, encoded>::value;
    EXPECT_TRUE(eq);
}

TEST(MetaVarintEncodeSequenceTests, EncodeTest3) {
    typedef VarintEncodeSequence<size_t, 150, 0xffff> encoded;
    bool eq = std::is_same<IntegralSequence<uint8_t, 150, 1, 255, 255, 3>, encoded>::value;
    EXPECT_TRUE(eq);
}