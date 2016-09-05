/**
 *  @autor tekatod
 *  @date 9/5/16
 */
#include <string>
#include <gtest/gtest.h>
#include "rrc/core/Advertiser.h"
#include "rrc/core/LinearLauncher.h"
#include "Message.pb.h"
#include "include/DummyNode.h"

using namespace rrc;

class SendGuardFixture : public ::testing::Test {
public:
    SendGuardFixture() : mTopicName("test") {
        mMetaTable.registerTypeId<testmessages::TestMessage>(1u);
        mRootNode = std::make_shared<RootNode>(&mLauncher, &mMetaTable);
        dummyNode1 = std::make_shared<DummyNode>(mRootNode, "test");
        mTimePoint = std::chrono::steady_clock::now();
    }

    ~SendGuardFixture() {
        //Destroy all the good members
    }

protected:
    MetaTable mMetaTable;
    RootNodePtr mRootNode;
    LinearLauncher mLauncher;
    std::shared_ptr<DummyNode> dummyNode1;
    std::string mTopicName;
    std::chrono::steady_clock::time_point mTimePoint;
};

TEST_F(SendGuardFixture, ExceptionTest) {
    EXPECT_THROW(SendGuard<testmessages::TestMessageContainer> sendGuard(mRootNode, mTopicName), UnregisteredTypeException);
}

TEST_F(SendGuardFixture, SendTest) {
    SendGuard<testmessages::TestMessage>  sendGuard(mRootNode, mTopicName);
    sendGuard->set_id(42);
    sendGuard->set_txt("42");
    sendGuard.send();
    mRootNode->entry();
    MessagePtr messagePtr= dummyNode1->tryGetMessage();
    const testmessages::TestMessage* testMessage = (testmessages::TestMessage*)messagePtr->getData();
    EXPECT_EQ(testMessage->id(), 42);
    EXPECT_EQ(testMessage->txt(), "42");
}

TEST_F(SendGuardFixture, IsSentTest) {
    SendGuard<testmessages::TestMessage>  sendGuard(mRootNode, mTopicName);
    sendGuard->set_id(42);
    sendGuard->set_txt("42");
    EXPECT_FALSE(sendGuard.isSent());
    sendGuard.send();
    mRootNode->entry();
    EXPECT_TRUE(sendGuard.isSent());
}

TEST_F(SendGuardFixture, GetSetTest) {
    SendGuard<testmessages::TestMessage>  sendGuard(mRootNode, mTopicName);
    sendGuard.setTimestamp(mTimePoint);
    EXPECT_EQ(sendGuard.getTimestamp(), mTimePoint);
}