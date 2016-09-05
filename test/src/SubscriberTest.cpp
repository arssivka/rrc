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
        mMetaTable.registerTypeId<message::TestMessage>(0);
        mRootNode = std::make_shared<RootNode>(mLauncher, mMetaTable);
    }

protected:
    MetaTable mMetaTable;
    LinearLauncher mLauncher;
    RootNodePtr mRootNode;
};


TEST_F(SubscriberFixture, CreateSubscriber) {
    EXPECT_NO_THROW(Subscriber<message::TestMessage>(mRootNode, "test"));
    EXPECT_THROW(Subscriber<message::TestMessageContainer>(mRootNode, "test"), UnregisteredTypeException);
}


TEST_F(SubscriberFixture, ReceiveMessageTest1) {
    Subscriber<message::TestMessage> subscriber(mRootNode, "test");

    TypeId typeId = mMetaTable.getTypeId<message::TestMessage>();
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::unique_ptr<message::TestMessage> data = std::make_unique<message::TestMessage>();
    data->set_id(42);
    MessagePtr message = std::make_shared<Message>(typeId, now, std::move(data));

    mRootNode->sendMessage("test", message);
    EXPECT_FALSE(subscriber.tryGetMessage().isMessageSet());
    mRootNode->entry();
    EXPECT_EQ(subscriber.tryGetMessage()->id(), 42);
    EXPECT_FALSE(subscriber.tryGetMessage().isMessageSet());
}


TEST_F(SubscriberFixture, ReceiveMessageTest2) {
    Subscriber<message::TestMessage> subscriber(mRootNode, "test");

    TypeId typeId = mMetaTable.getTypeId<message::TestMessageContainer>();
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::unique_ptr<message::TestMessageContainer> data = std::make_unique<message::TestMessageContainer>();
    MessagePtr message = std::make_shared<Message>(typeId, now, std::move(data));

    mRootNode->sendMessage("test", message);
    EXPECT_FALSE(subscriber.tryGetMessage().isMessageSet());
    mRootNode->entry();
    EXPECT_FALSE(subscriber.tryGetMessage().isMessageSet());
}
