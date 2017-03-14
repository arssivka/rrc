/**
 *  @autor tekatod
 *  @date 2/7/17
 */

#include <iostream>
#include <gtest/gtest.h>
#include <rrc/rrc.h>
#include <flag_setter.h>

using namespace rrc;

TEST(concurrent_task_queue_tests, rvalue_test) {
    bool flag = false;
    concurrent_task_queue queue;
    concurrent_task_queue::task_type task;
    EXPECT_FALSE(queue.try_dequeue(task));
    queue.enqueue(flag_setter(flag));
    EXPECT_TRUE(queue.try_dequeue(task));
    EXPECT_FALSE(queue.try_dequeue(task));
    queue.enqueue(flag_setter(flag));
    queue.enqueue(flag_setter(flag));
    EXPECT_TRUE(queue.try_dequeue(task));
    EXPECT_TRUE(queue.try_dequeue(task));
    EXPECT_FALSE(flag);
}

TEST(concurrent_task_queue_tests, lvalue_test) {
    bool flag1 = false;
    bool flag2 = true;
    concurrent_task_queue queue;
    concurrent_task_queue::task_type task = flag_setter(flag1);
    EXPECT_FALSE(queue.try_dequeue(task));
    queue.enqueue(flag_setter(flag2));
    EXPECT_TRUE(queue.try_dequeue(task));
    EXPECT_FALSE(queue.try_dequeue(task));
    task();
    EXPECT_FALSE(flag1);
    EXPECT_TRUE(flag2);
}