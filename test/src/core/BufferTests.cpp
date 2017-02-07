/**
 *  @autor tekatod
 *  @date 2/7/17
 */

#include <iostream>
#include <gtest/gtest.h>
#include <rrc/core/Buffer.h>

using namespace rrc;

TEST(BufferTests, BasicTest) {
    uint8_t buf[] = {1, 0, 1, 0, 1};
    Buffer testBuffer(buf, 5);
    EXPECT_EQ(testBuffer.getSize(), (size_t) 5);
    EXPECT_FALSE(testBuffer.isEmpty());
    EXPECT_EQ(testBuffer.getBufferPointer()[0], buf[0]);
    EXPECT_EQ(testBuffer.getBufferPointer()[4], buf[4]);
}

TEST(BufferTest, EmptyTest) {
    uint8_t buf[] = {1, 0, 1, 0, 1};
    Buffer testBuffer(buf, 0);
    EXPECT_TRUE(testBuffer.isEmpty());
    EXPECT_EQ(testBuffer.getBufferPointer(), nullptr);
}


TEST(BufferTest, EqTest) {
    uint8_t buf[] = {1, 0, 1, 0, 1};
    uint8_t buf1[] = {1, 1, 1, 0, 1};
    uint8_t buf2[] = {1, 0, 1, 0, 1, 0};
    Buffer testBuffer(buf, 5);
    Buffer testBuffer1(buf, 5);
    Buffer testBuffer2(buf1, 5);
    Buffer testBuffer3(buf2, 6);
    EXPECT_TRUE(testBuffer == testBuffer1);
    EXPECT_FALSE(testBuffer == testBuffer2);
    EXPECT_FALSE(testBuffer == testBuffer3);
    EXPECT_TRUE(testBuffer2 != testBuffer3);
}

TEST(BufferTests, IteratorTest) {
    uint8_t buf[] = {0, 1, 2, 3, 4};
    Buffer testBuffer(buf, 5);
    uint8_t check = 0;
    uint8_t sum = 0;
    for(auto it = testBuffer.begin(); it != testBuffer.end(); ++it) {
        check++;
    }
    EXPECT_EQ(check, (uint8_t)5);
    for(auto item : testBuffer) {
        check++;
        sum += item;
    }
    EXPECT_EQ(check, 10);
    EXPECT_EQ(sum, 10);
    std::vector<uint8_t> checkVector{4, 3, 2, 1, 0};
    std::vector<uint8_t> fillVector;
    for(auto it = testBuffer.rbegin(); it != testBuffer.rend(); ++it) {
        fillVector.push_back(*it);
    }
    EXPECT_EQ(checkVector, fillVector);
}

TEST(BufferTests, CopyTest) {
    uint8_t buf[] = {0, 1, 2, 3, 4};
    Buffer testBuffer(buf, 5);
    Buffer testBuffer1(testBuffer);
    EXPECT_TRUE(testBuffer == testBuffer1);
}

TEST(BufferTests, MoveTest) {
    uint8_t buf[] = {0, 1, 2, 3, 4};
    Buffer testBuffer(Buffer(buf, 5));
    EXPECT_EQ(testBuffer.getBufferPointer()[0], buf[0]);
    EXPECT_EQ(testBuffer.getBufferPointer()[4], buf[4]);
    Buffer testBuffer1(buf, 5);
    EXPECT_TRUE(testBuffer == testBuffer1);
}