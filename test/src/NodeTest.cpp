/**
 *  @autor arssivka
 *  @date 9/5/16
 */

#include <gtest/gtest.h>
#include <rrc/core/MetaTable.h>
#include <rrc/core/LinearLauncher.h>
#include <Message.pb.h>
#include <include/DummyNode.h>

using namespace rrc;


class NodeFixture : public ::testing::Test {
public:
    NodeFixture() {
        mMetaTable.registerTypeId<message::TestMessage>(0);
        mRootNode = std::make_shared<RootNode>(mLinearLauncher, mMetaTable);
    }

protected:
    MetaTable mMetaTable;
    LinearLauncher mLinearLauncher;
    RootNodePtr mRootNode;
};


TEST_F(NodeFixture, CreateAdvertiserTest) {
    DummyNode dummyNode(mRootNode, "test");
    EXPECT_NO_THROW(dummyNode.createAdvertiser<message::TestMessage>("test"));
    EXPECT_THROW(dummyNode.createAdvertiser<message::TestMessageContainer>("test"),
                 UnregisteredTypeException);
}

TEST_F(NodeFixture, CreatedSubscriberTest) {
    DummyNode dummyNode(mRootNode, "test");
    EXPECT_NO_THROW(dummyNode.createSubscriber<message::TestMessage>("test"));
    EXPECT_THROW(dummyNode.createSubscriber<message::TestMessageContainer>("test"),
                 UnregisteredTypeException);
}
