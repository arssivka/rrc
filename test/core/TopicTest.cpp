/**
 *  @autor tekatod
 *  @date 9/1/16
 */
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/Topic.h"
#include "Message.pb.h"

using namespace rrc;

class TopicFixture : public ::testing::Test {
public:
    TopicFixture() : mRightMessageListenerPtr(std::make_shared<MessageListener>(1u)),
                        mWrongMessageListenerPtr(std::make_shared<MessageListener>(2u)) {
        mMetaTable.registerTypeId<message::TestMessage>(1u);
        mMetaTable.registerTypeId<message::TestMessageContainer>(2u);

    }

    ~TopicFixture() {
        //Destroy all the good members
    }

protected:
    MessageListenerPtr mRightMessageListenerPtr;
    MessageListenerPtr mWrongMessageListenerPtr;
    MetaTable mMetaTable;
};


TEST_F(TopicFixture, AddListenerTest) {
    Topic tstTopic(mMetaTable.getTypeId<message::TestMessage>());
    EXPECT_TRUE(tstTopic.addListener(mRightMessageListenerPtr));
    EXPECT_FALSE(tstTopic.addListener(mWrongMessageListenerPtr));
}


TEST_F(TopicFixture, CheckTest) {
    Topic tstTopic(mMetaTable.getTypeId<message::TestMessage>());
    EXPECT_TRUE(tstTopic.checkCapability(mMetaTable.getTypeId<message::TestMessage>()));
    EXPECT_FALSE(tstTopic.checkCapability(2u));
}


TEST_F(TopicFixture, EmptyTrueTest) {
    Topic tstTopic(mMetaTable.getTypeId<message::TestMessage>());
    EXPECT_TRUE(tstTopic.empty());
    tstTopic.addListener(mRightMessageListenerPtr);
    EXPECT_FALSE(tstTopic.empty());
}


TEST_F(TopicFixture, RemoveTest) {
    Topic tstTopic(mMetaTable.getTypeId<message::TestMessage>());
    tstTopic.addListener(mRightMessageListenerPtr);
    tstTopic.removeListener(mRightMessageListenerPtr);
    EXPECT_TRUE(tstTopic.empty());
}

TEST_F(TopicFixture, SendTest) {
    Topic tstTopic(mMetaTable.getTypeId<message::TestMessage>());
    tstTopic.addListener(mRightMessageListenerPtr);
    message::TestMessage tstMessage;
    tstMessage.set_id(42);
    tstMessage.set_txt("42");
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    MessagePtr messagePtr = std::make_shared<Message>(mMetaTable.getTypeId<message::TestMessage>(), now,
                                                                std::make_unique<message::TestMessage>(tstMessage));
    tstTopic.sendMessage(messagePtr);
    EXPECT_NE(mRightMessageListenerPtr->tryDequeueMessage(), nullptr);
    EXPECT_EQ(mRightMessageListenerPtr->tryDequeueMessage(), nullptr);
    MessagePtr messagePtr2 = std::make_shared<Message>(mMetaTable.getTypeId<message::TestMessageContainer>(), now,
                                                      std::make_unique<message::TestMessage>(tstMessage));
    tstTopic.sendMessage(messagePtr2);
    EXPECT_EQ(mRightMessageListenerPtr->tryDequeueMessage(), nullptr);
}

