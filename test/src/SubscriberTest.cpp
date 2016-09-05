/**
 *  @autor arssivka
 *  @date 9/5/16
 */

#include <gtest/gtest.h>
#include <rrc/core/MetaTable.h>
#include <rrc/core/RootNode.h>
#include <rrc/core/LinearLauncher.h>
#include <rrc/core/Subscriber.h>
#include <Message.pb.h>

using namespace rrc;


class SubscriberFixture : public ::testing::Test {
public:
    SubscriberFixture() {
        mMetaTable.registerTypeId<testmessages::TestMessage>(0);
        mRootNode = std::make_shared<RootNode>(mLauncher, mMetaTable);
    }

protected:
    MetaTable mMetaTable;
    LinearLauncher mLauncher;
    RootNodePtr mRootNode;
};


TEST_F(SubscriberFixture, CreateSubscriber) {
    EXPECT_NO_THROW(Subscriber<testmessages::TestMessage>(mRootNode, "test"));
    EXPECT_THROW(Subscriber<testmessages::TestMessageContainer>(mRootNode, "test"), UnregisteredTypeException);
}


TEST_F(SubscriberFixture, ReceiveMessageTest1) {
    Subscriber<testmessages::TestMessage> subscriber(mRootNode, "test");

    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessage>();
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::unique_ptr<testmessages::TestMessage> data = std::make_unique<testmessages::TestMessage>();
    data->set_id(42);
    MessagePtr message = std::make_shared<Message>(typeId, now, std::move(data));

    mRootNode->sendMessage("test", message);
    EXPECT_FALSE(subscriber.tryGetMessage().isMessageSet());
    mRootNode->entry();
    EXPECT_EQ(subscriber.tryGetMessage()->id(), 42);
    EXPECT_FALSE(subscriber.tryGetMessage().isMessageSet());
}


TEST_F(SubscriberFixture, ReceiveMessageTest2) {
    Subscriber<testmessages::TestMessage> subscriber(mRootNode, "test");

    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessageContainer>();
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::unique_ptr<testmessages::TestMessageContainer> data = std::make_unique<testmessages::TestMessageContainer>();
    MessagePtr message = std::make_shared<Message>(typeId, now, std::move(data));

    mRootNode->sendMessage("test", message);
    EXPECT_FALSE(subscriber.tryGetMessage().isMessageSet());
    mRootNode->entry();
    EXPECT_FALSE(subscriber.tryGetMessage().isMessageSet());
}
