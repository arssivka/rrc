/**
 *  @autor tekatod
 *  @date 1/20/17
 */

#include <rrc/meta/MetaVarintEncode.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"


using namespace rrc;

TEST(MetaVarintTests, EncodeTest1) {
    typedef MetaVarintEncode<uint64_t, 150> encoded;
    bool eq = std::is_same<MetaIntegralSequence<uint8_t, 150, 1>, encoded>::value;
    EXPECT_TRUE(eq);
}

TEST(MetaVarintTests, EncodeTest2) {
    typedef MetaVarintEncode<uint64_t, 0xffff> encoded;
    bool eq = std::is_same<MetaIntegralSequence<uint8_t, 255, 255, 3>, encoded>::value;
    EXPECT_TRUE(eq);
}