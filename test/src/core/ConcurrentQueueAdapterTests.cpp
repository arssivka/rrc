/**
 *  @autor tekatod
 *  @date 2/7/17
 */

#include <iostream>
#include <gtest/gtest.h>
#include <rrc/core/ConcurrentQueueAdapter.h>

using namespace rrc;

TEST(ConcurrentQueueAdapterTests, RValueTest) {
    ConcurrentQueueAdapter<int> testQueue;
    testQueue.enqueue(1);
    int x;
    EXPECT_TRUE(testQueue.tryDequeue(x));
    EXPECT_EQ(x, (int) 1);
    EXPECT_FALSE(testQueue.tryDequeue(x));
    testQueue.enqueue(2);
    testQueue.enqueue(3);
    EXPECT_TRUE(testQueue.tryDequeue(x));
    EXPECT_EQ(x, (int) 2);
    EXPECT_TRUE(testQueue.tryDequeue(x));
    EXPECT_EQ(x, (int) 3);

}

TEST(ConcurrentQueueAdapterTests, LValueTest) {
    ConcurrentQueueAdapter<int> testQueue;
    int x = 1;
    testQueue.enqueue(x);
    int y;
    EXPECT_TRUE(testQueue.tryDequeue(y));
    EXPECT_EQ(y, (int) 1);
    EXPECT_FALSE(testQueue.tryDequeue(y));
}