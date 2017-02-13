/**
 *  @autor tekatod
 *  @date 2/13/17
 */

#include <gtest/gtest.h>
#include <rrc/core/AbstracrTaskQueueAdapter.h>
#include <rrc/core/STLQueueAdapter.h>
#include <rrc/core/Service.h>

using namespace rrc;

class ServiceFixture : public ::testing::Test {
public:
    ServiceFixture() {
        testAdapter = (AbstracrTaskQueueAdapter*) new STLQueueAdapter<Task>();
        resultAdapter = (AbstracrTaskQueueAdapter*) new STLQueueAdapter<Task>();
    }

protected:
    AbstracrTaskQueueAdapter* testAdapter;
    AbstracrTaskQueueAdapter* resultAdapter;
};

TEST_F(ServiceFixture, BasicNonConstConstructorTests) {
    std::shared_ptr<AbstracrTaskQueueAdapter> testAdapterPtr(testAdapter);
    std::shared_ptr<AbstracrTaskQueueAdapter> resultAdapterPtr(resultAdapter);
    uint8_t buf[] = {1, 0, 1, 0, 1};
    Buffer testBuffer(buf, 5);
    Buffer resultBuffer(buf, 0);
    std::shared_ptr<TaskHub> taskHub = std::make_shared<TaskHub>(resultAdapterPtr, [&resultBuffer](const Buffer& buffer){
        resultBuffer = buffer;
    });
    Service service(testAdapterPtr, [](const Buffer& b){
        return std::make_shared<Buffer>(b);
    });
    service.call(taskHub, std::make_shared<Buffer>(testBuffer));
    EXPECT_TRUE(testAdapterPtr->execOnce());
    EXPECT_TRUE(resultAdapterPtr->execOnce());
    EXPECT_EQ(testBuffer, resultBuffer);
}

std::shared_ptr<Buffer> makeSmth2(const Buffer& buffer) {
    return std::make_shared<Buffer>(buffer);
}

TEST_F(ServiceFixture, BasicConstConstructorTests) {
    std::shared_ptr<AbstracrTaskQueueAdapter> testAdapterPtr(testAdapter);
    std::shared_ptr<AbstracrTaskQueueAdapter> resultAdapterPtr(resultAdapter);
    uint8_t buf[] = {1, 0, 1, 0, 1};
    Buffer testBuffer(buf, 5);
    Buffer resultBuffer(buf, 0);
    std::shared_ptr<TaskHub> taskHub = std::make_shared<TaskHub>(resultAdapterPtr, [&resultBuffer](const Buffer& buffer){
        resultBuffer = buffer;
    });
    Service service(testAdapterPtr, &makeSmth2);
    service.call(taskHub, std::make_shared<Buffer>(testBuffer));
    EXPECT_TRUE(testAdapterPtr->execOnce());
    EXPECT_TRUE(resultAdapterPtr->execOnce());
    EXPECT_EQ(testBuffer, resultBuffer);
}