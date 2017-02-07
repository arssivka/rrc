/**
 *  @autor tekatod
 *  @date 2/7/17
 */

#include <gtest/gtest.h>
#include <rrc/core/AbstracrTaskQueueAdapter.h>
#include <rrc/core/STLQueueAdapter.h>

using namespace rrc;

TEST(TaskQueueAdapterTests, ExecOnceTest) {
    AbstracrTaskQueueAdapter* testAdapter = (AbstracrTaskQueueAdapter*) new STLQueueAdapter<Task>();
    int r;
    testAdapter->enqueueTask([](int x1, int x2, int& x3) {
        x3 = x1 + x2;
    }, 40, 2, std::ref(r));
    EXPECT_TRUE(testAdapter->execOnce());
    EXPECT_EQ(r, (int) 42);
}

TEST(TaskQueueAdapterTests, ExecAllTest) {
    AbstracrTaskQueueAdapter* testAdapter = (AbstracrTaskQueueAdapter*) new STLQueueAdapter<Task>();
    int r;
    int r1;
    int r2;
    testAdapter->enqueueTask([](int x1, int x2, int& x3) {
        x3 = x1 + x2;
    }, 40, 2, std::ref(r));
    testAdapter->enqueueTask([](int x1, int& x3) {
        x3 = x1;
    }, 42, std::ref(r1));
    testAdapter->enqueueTask([](int x1, int x2, int& x3) {
        x3 = x1 - x2;
    }, 44, 2, std::ref(r2));
    testAdapter->execAll();
    EXPECT_EQ(r, (int) 42);
    EXPECT_EQ(r1, (int) 42);
    EXPECT_EQ(r2, (int) 42);
}