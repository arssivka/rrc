/**
 *  @autor tekatod
 *  @date 2/13/17
 */

#include <gtest/gtest.h>
#include <rrc/core/AbstracrTaskQueueAdapter.h>
#include <rrc/core/STLQueueAdapter.h>
#include <rrc/core/TaskHub.h>

using namespace rrc;

class TaskHubFixture : public ::testing::Test {
public:
    TaskHubFixture() {
        testAdapter = (AbstracrTaskQueueAdapter*) new STLQueueAdapter<Task>();
    }

protected:
    AbstracrTaskQueueAdapter* testAdapter;
};

TEST_F(TaskHubFixture, BasicNonConstConstructorTests) {
    std::shared_ptr<AbstracrTaskQueueAdapter> testAdapterPtr(testAdapter);
    TaskHub taskHub(testAdapterPtr, [](const Buffer& buffer){
        buffer.isEmpty();
    });
    uint8_t buf[] = {1, 0, 1, 0, 1};
    Buffer testBuffer(buf, 5);
    taskHub.enqueueTask(std::make_shared<Buffer>(testBuffer));
    EXPECT_FALSE(taskHub.isOrphan());
    EXPECT_TRUE(testAdapterPtr->execOnce());
}

void makeSmth(const Buffer& buffer) {
    buffer.isEmpty();
}

TEST_F(TaskHubFixture, BasicOrphanTests) {
    std::shared_ptr<AbstracrTaskQueueAdapter> testAdapterPtr(testAdapter);
    TaskHub taskHub(testAdapterPtr, &makeSmth);
    uint8_t buf[] = {1, 0, 1, 0, 1};
    Buffer testBuffer(buf, 5);
    taskHub.enqueueTask(std::make_shared<Buffer>(testBuffer));
    EXPECT_FALSE(taskHub.isOrphan());
    EXPECT_TRUE(testAdapterPtr->execOnce());
}