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


class AdvertiserFixture : public ::testing::Test {
public:
    AdvertiserFixture() : mTopicName("test") {
        mMetaTable.registerTypeId<message::TestMessage>(1u);
        mRootNode = std::make_shared<RootNode>(&mLauncher, &mMetaTable);
        dummyNode1 = std::make_shared<DummyNode>(mRootNode, "test");
    }

    ~AdvertiserFixture() {
        //Destroy all the good members
    }

protected:
    MetaTable mMetaTable;
    RootNodePtr mRootNode;
    LinearLauncher mLauncher;
    std::shared_ptr<DummyNode> dummyNode1;
    std::string mTopicName;
};


TEST_F(AdvertiserFixture, ExceptionTest) {
    EXPECT_THROW(Advertiser<message::TestMessageContainer> advertiser(mRootNode, mTopicName), UnregisteredTypeException);
}


TEST_F(AdvertiserFixture, SendGuardTest) {
    Advertiser<message::TestMessage> advertiser(mRootNode, mTopicName);
    SendGuard<message::TestMessage> sendGuard = advertiser.createSendGuard();
    sendGuard->set_id(42);
    sendGuard->set_txt("42");
    sendGuard.send();
    mRootNode->entry();
    MessagePtr messagePtr= dummyNode1->tryGetMessage();
    const message::TestMessage* testMessage = (message::TestMessage*)messagePtr->getData();
    EXPECT_EQ(testMessage->id(), 42);
    EXPECT_EQ(testMessage->txt(), "42");
}