/**
 *  @autor tekatod
 *  @date 2/7/17
 */

#include <iostream>
#include <gtest/gtest.h>
#include <rrc/core.h>

using namespace rrc;

TEST(stl_queue_adapter_tests, rvalue_test) {
    stl_queue_adapter<int> queue;
    queue.enqueue(1);
    int x;
    EXPECT_TRUE(queue.try_dequeue(x));
    EXPECT_EQ(x, (int) 1);
    EXPECT_FALSE(queue.try_dequeue(x));
    queue.enqueue(2);
    queue.enqueue(3);
    EXPECT_TRUE(queue.try_dequeue(x));
    EXPECT_EQ(x, (int) 2);
    EXPECT_TRUE(queue.try_dequeue(x));
    EXPECT_EQ(x, (int) 3);

}

TEST(stl_queue_adapter_tests, lvalue_test) {
    stl_queue_adapter<int> queue;
    int x = 1;
    queue.enqueue(x);
    int y;
    EXPECT_TRUE(queue.try_dequeue(y));
    EXPECT_EQ(y, (int) 1);
    EXPECT_FALSE(queue.try_dequeue(y));
}