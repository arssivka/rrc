/**
 *  @autor tekatod
 *  @date 1/20/17
 */

#include "gtest/gtest.h"
#include <rrc/core/Varint.h>
#include "gmock/gmock.h"

using namespace rrc;

TEST(VarintTests, EnocdeTest) {
    uint8_t buf[5] = {};
    uint8_t testbuf[5] = {150, 1, 0, 0, 0};
    size_t outsize = Varint::encode<uint64_t>(150, buf);
    EXPECT_EQ((size_t) 2, outsize);
    EXPECT_THAT(testbuf, testing::ElementsAreArray(buf));
}

TEST(VarintTests, DecodeTest) {
    uint8_t testbuf[5] = {150, 1, 0, 0, 0};
    uint64_t decoded = Varint::decode<uint64_t>(testbuf);
    EXPECT_EQ(decoded, (uint64_t) 150);
}

TEST(VarintTests, EnocdeDecodeTest) {
    uint8_t buf[5];
    size_t outsize =Varint::encode<uint64_t>(0xcafe, buf);
    uint64_t decoded = Varint::decode<uint64_t>(buf);
    EXPECT_EQ((size_t) 3, outsize);
    EXPECT_EQ(decoded, (uint64_t) 0xcafe);
}

TEST(VarintTest, EnocodeDecodeShortTest) {
    uint8_t buf[3] = {};
    uint8_t testbuf[3] = {255, 255, 3};
    size_t outsize = Varint::encode<uint16_t>(0xffff, buf);
    EXPECT_EQ((size_t) 3, outsize);
    EXPECT_THAT(testbuf, testing::ElementsAreArray(buf));
    uint16_t decoded = Varint::decode(testbuf);
    EXPECT_EQ(decoded, (uint16_t) 0xffff);
}

TEST(VarintTests, EncodeDecodeLongTest) {
    uint8_t buf[9];
    size_t outsize = Varint::encode<uint64_t>(0xffffffffffffffff, buf);
    uint64_t decoded = Varint::decode<uint64_t>(buf);
    EXPECT_EQ((size_t) 9, outsize);
    EXPECT_EQ(decoded, (uint64_t) 0xffffffffffffffff);
}