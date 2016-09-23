/**
 *  @autor tekatod
 *  @date 9/1/16
 */
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <rrc/core/Topic.h>
#include <rrc/core/QueueMessageListener.h>
#include "Message.pb.h"

using namespace rrc;

class TopicFixture : public ::testing::Test {
public:
    TopicFixture() : mRightMessageListenerPtr(std::make_shared<QueueMessageListener>(1u)),
                        mWrongMessageListenerPtr(std::make_shared<QueueMessageListener>(2u)) {
        mMetaTable.registerTypeId<testmessages::TestMessage>(1u);
        mMetaTable.registerTypeId<testmessages::TestMessageContainer>(2u);

    }

    ~TopicFixture() {
        //Destroy all the good members
    }

protected:
    QueueMessageListenerPtr mRightMessageListenerPtr;
    QueueMessageListenerPtr mWrongMessageListenerPtr;
    MetaTable mMetaTable;
};


TEST_F(TopicFixture, AddListenerTest) {
    Topic tstTopic(mMetaTable.getTypeId<testmessages::TestMessage>());
    EXPECT_TRUE(tstTopic.addListener(mRightMessageListenerPtr));
    EXPECT_FALSE(tstTopic.addListener(mWrongMessageListenerPtr));
}


TEST_F(TopicFixture, CheckTest) {
    Topic tstTopic(mMetaTable.getTypeId<testmessages::TestMessage>());
    EXPECT_TRUE(tstTopic.checkCapability(mMetaTable.getTypeId<testmessages::TestMessage>()));
    EXPECT_FALSE(tstTopic.checkCapability(2u));
}


TEST_F(TopicFixture, EmptyTrueTest) {
    Topic tstTopic(mMetaTable.getTypeId<testmessages::TestMessage>());
    EXPECT_FALSE(tstTopic.hasListeners());
    tstTopic.addListener(mRightMessageListenerPtr);
    EXPECT_TRUE(tstTopic.hasListeners());
}


TEST_F(TopicFixture, RemoveTest) {
    Topic tstTopic(mMetaTable.getTypeId<testmessages::TestMessage>());
    tstTopic.addListener(mRightMessageListenerPtr);
    tstTopic.removeListener(mRightMessageListenerPtr);
    EXPECT_FALSE(tstTopic.hasListeners());
}

TEST_F(TopicFixture, SendTest) {
    Topic tstTopic(mMetaTable.getTypeId<testmessages::TestMessage>());
    tstTopic.addListener(mRightMessageListenerPtr);
    testmessages::TestMessage tstMessage;
    tstMessage.set_id(42);
    tstMessage.set_txt("42");

    MessagePtr messagePtr = std::make_shared<Message>(
            mMetaTable.getTypeId<testmessages::TestMessage>(),
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>(std::move(tstMessage))
    );

    tstTopic.sendMessage(messagePtr);
    EXPECT_NE(mRightMessageListenerPtr->tryDequeueMessage(), nullptr);
    EXPECT_EQ(mRightMessageListenerPtr->tryDequeueMessage(), nullptr);

    MessagePtr messagePtr2 = std::make_shared<Message>(
            mMetaTable.getTypeId<testmessages::TestMessageContainer>(),
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>(tstMessage)
    );

    tstTopic.sendMessage(messagePtr2);
    EXPECT_EQ(mRightMessageListenerPtr->tryDequeueMessage(), nullptr);
}

