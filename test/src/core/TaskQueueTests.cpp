/**
 *  @autor arssivka
 *  @date 9/2/16
 */

#include <rrc/core/TaskQueue.h>
#include <gtest/gtest.h>

using namespace rrc;


TEST(TaskQueueTest, DequeueFromEmptyQueue) {
    TaskQueue queue;
    Task task;
    EXPECT_FALSE(queue.tryDequeue(task));
}


TEST(TaskQueueTest, InsertingTest1) {
    TaskQueue queue;
    Task task = []() { };
    queue.enqueue(task);
    EXPECT_TRUE(queue.tryDequeue(task));
    EXPECT_FALSE(queue.tryDequeue(task));
}


TEST(TaskQueueTest, InsertingTest2) {
    TaskQueue queue;
    Task task = []() { };
    queue.enqueue(task);
    queue.enqueue(task);
    EXPECT_TRUE(queue.tryDequeue(task));
    EXPECT_TRUE(queue.tryDequeue(task));
    EXPECT_FALSE(queue.tryDequeue(task));
}


TEST(TaskQueue, ExecOnceTest) {
    TaskQueue queue;
    int counter = 0;
    Task task = [&counter]() {
        ++counter;
    };

    queue.enqueue(task);
    queue.enqueue(task);
    EXPECT_TRUE(queue.execOnce());
    EXPECT_EQ(counter, 1);
    EXPECT_TRUE(queue.execOnce());
    EXPECT_EQ(counter, 2);
    EXPECT_FALSE(queue.execOnce());
    EXPECT_EQ(counter, 2);
}


TEST(TaskQueue, ExecAllTest) {
    TaskQueue queue;
    int counter = 0;
    Task task = [&counter]() {
        ++counter;
    };

    queue.enqueue(task);
    queue.enqueue(task);
    queue.execAll();
    EXPECT_EQ(counter, 2);
    EXPECT_FALSE(queue.execOnce());
    EXPECT_EQ(counter, 2);
}


TEST(TaskQueue, InsertWithBindingTest) {
    TaskQueue queue;
    int counter1 = 0;
    int counter2 = 0;
    auto func = [](int& var, int value) {
        var = value;
    };

    queue.enqueue(func, std::ref(counter1), 1);
    queue.enqueue(func, std::ref(counter2), 2);
    EXPECT_EQ(counter1, 0);
    EXPECT_EQ(counter2, 0);
    queue.execAll();
    EXPECT_EQ(counter1, 1);
    EXPECT_EQ(counter2, 2);
}

