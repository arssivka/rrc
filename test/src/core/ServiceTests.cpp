/**
 *  @autor tekatod
 *  @date 2/13/17
 */

#include <gtest/gtest.h>
#include <rrc/core/AbstractTaskQueueAdapter.h>
#include <rrc/core/STLQueueAdapter.h>
#include <rrc/core/Service.h>

using namespace rrc;

class ServiceFixture
        : public ::testing::Test {
public:
    ServiceFixture() {
        testAdapter = (AbstractTaskQueueAdapter*) new STLQueueAdapter<Task>();
        resultAdapter = (AbstractTaskQueueAdapter*) new STLQueueAdapter<Task>();
    }


protected:
    AbstractTaskQueueAdapter* testAdapter;
    AbstractTaskQueueAdapter* resultAdapter;
};

TEST_F(ServiceFixture, BasicNonConstConstructorTests) {
    std::shared_ptr<AbstractTaskQueueAdapter> testAdapterPtr(testAdapter);
    std::shared_ptr<AbstractTaskQueueAdapter> resultAdapterPtr(resultAdapter);
    uint8_t buf[] = {1, 0, 1, 0, 1};
    Buffer testBuffer(buf, 5);
    Buffer resultBuffer(buf, 0);
    std::shared_ptr<TaskHub<Buffer>> taskHub = std::make_shared<TaskHub<Buffer>>(
            resultAdapterPtr, [&resultBuffer](const TaskHub<Buffer>::Pointer buffer) {
                resultBuffer = *buffer;
            });
    Service service(testAdapterPtr, [](const std::shared_ptr<Buffer> b) {
        return b;
    });
    service.call(taskHub, std::make_shared<Buffer>(testBuffer));
    EXPECT_TRUE(testAdapterPtr->execOnce());
    EXPECT_TRUE(resultAdapterPtr->execOnce());
    EXPECT_EQ(testBuffer, resultBuffer);
}


std::shared_ptr<Buffer> makeSmth2(const std::shared_ptr<Buffer> buffer) {
    return  buffer;
}


TEST_F(ServiceFixture, BasicConstConstructorTests) {
    std::shared_ptr<AbstractTaskQueueAdapter> testAdapterPtr(testAdapter);
    std::shared_ptr<AbstractTaskQueueAdapter> resultAdapterPtr(resultAdapter);
    uint8_t buf[] = {1, 0, 1, 0, 1};
    Buffer testBuffer(buf, 5);
    Buffer resultBuffer(buf, 0);
    std::shared_ptr<TaskHub<Buffer>> taskHub = std::make_shared<TaskHub<Buffer>>(
            resultAdapterPtr,
            [&resultBuffer](const TaskHub<Buffer>::Pointer buffer) {
                resultBuffer = *buffer;
            });
    Service service(testAdapterPtr, &makeSmth2);
    service.call(taskHub, std::make_shared<Buffer>(testBuffer));
    EXPECT_TRUE(testAdapterPtr->execOnce());
    EXPECT_TRUE(resultAdapterPtr->execOnce());
    EXPECT_EQ(testBuffer, resultBuffer);
}