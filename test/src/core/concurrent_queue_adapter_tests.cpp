/**
 *  @autor tekatod
 *  @date 2/7/17
 */

#include <iostream>
#include <gtest/gtest.h>
#include <rrc/core/concurrent_queue_adapter.h>

using namespace rrc;

TEST(concurrent_queue_adapter_tests, r_value_test) {
    concurrent_queue_adapter<int> test_queue;
    test_queue.enqueue(1);
    int x;
    EXPECT_TRUE(test_queue.try_dequeue(x));
    EXPECT_EQ(x, (int) 1);
    EXPECT_FALSE(test_queue.try_dequeue(x));
    test_queue.enqueue(2);
    test_queue.enqueue(3);
    EXPECT_TRUE(test_queue.try_dequeue(x));
    EXPECT_EQ(x, (int) 2);
    EXPECT_TRUE(test_queue.try_dequeue(x));
    EXPECT_EQ(x, (int) 3);

}

TEST(concurrent_queue_adapter_tests, l_value_test) {
    concurrent_queue_adapter<int> test_queue;
    int x = 1;
    test_queue.enqueue(x);
    int y;
    EXPECT_TRUE(test_queue.try_dequeue(y));
    EXPECT_EQ(y, (int) 1);
    EXPECT_FALSE(test_queue.try_dequeue(y));
}