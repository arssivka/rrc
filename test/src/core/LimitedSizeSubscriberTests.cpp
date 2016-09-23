/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#include <gtest/gtest.h>
#include <rrc/core/LimitedSizeMessageListener.h>
#include <Message.pb.h>


using namespace rrc;

class LimitedSizeListenerFixture : public ::testing::Test {
public:
    LimitedSizeListenerFixture() {
        mMetaTable.registerTypeId<testmessages::TestMessage>(1);
        mMetaTable.registerTypeId<testmessages::TestMessageContainer>(2);
    }

    ~LimitedSizeListenerFixture() {
        //Destroy all the good members
    }

protected:
    MetaTable mMetaTable;

};


TEST_F(LimitedSizeListenerFixture, GetTypeId) {
    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessage>();
    LimitedSizeMessageListener<2> listener(typeId);
    EXPECT_EQ(listener.getTypeId(), typeId);
}


TEST_F(LimitedSizeListenerFixture, GetMessageFromEmptyQueue) {
    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessage>();
    LimitedSizeMessageListener<2> listener(typeId);
    EXPECT_EQ(listener.tryDequeueMessage(), nullptr);
}


TEST_F(LimitedSizeListenerFixture, GetMessages1) {
    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessage>();
    LimitedSizeMessageListener<2> listener(typeId);
    MessagePtr message = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>()
    );
    listener.enqueueMessage(message);
    ASSERT_EQ(listener.tryDequeueMessage(), message);
    ASSERT_EQ(listener.tryDequeueMessage(), nullptr);
}


TEST_F(LimitedSizeListenerFixture, GetMessages2) {
    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessage>();
    LimitedSizeMessageListener<2> listener(typeId);
    MessagePtr message = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>()
    );
    listener.enqueueMessage(message);
    listener.enqueueMessage(message);
    ASSERT_EQ(listener.tryDequeueMessage(), message);
    ASSERT_EQ(listener.tryDequeueMessage(), message);
    ASSERT_EQ(listener.tryDequeueMessage(), nullptr);
}


TEST_F(LimitedSizeListenerFixture, GetMessages3) {
    TypeId typeId1 = mMetaTable.getTypeId<testmessages::TestMessage>();
    TypeId typeId2 = mMetaTable.getTypeId<testmessages::TestMessageContainer>();
    LimitedSizeMessageListener<2> listener(typeId1);

    MessagePtr message1 = std::make_shared<Message>(
            typeId1,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>()
    );

    MessagePtr message2 = std::make_shared<Message>(
            typeId2,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessageContainer>()
    );

    listener.enqueueMessage(message1);
    listener.enqueueMessage(message2);
    ASSERT_EQ(listener.tryDequeueMessage(), message1);
    ASSERT_EQ(listener.tryDequeueMessage(), nullptr);
}


TEST_F(LimitedSizeListenerFixture, GetMessages4) {
    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessage>();
    LimitedSizeMessageListener<2> listener(typeId);

    MessagePtr message1 = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>()
    );

    MessagePtr message2 = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessageContainer>()
    );

    MessagePtr message3 = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessageContainer>()
    );

    MessagePtr message4 = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessageContainer>()
    );

    listener.enqueueMessage(message1);
    listener.enqueueMessage(message2);
    listener.enqueueMessage(message3);
    listener.enqueueMessage(message4);
    ASSERT_TRUE(message1.unique());
    ASSERT_TRUE(message2.unique());
    ASSERT_EQ(listener.tryDequeueMessage(), message3);
    ASSERT_EQ(listener.tryDequeueMessage(), message4);
    ASSERT_EQ(listener.tryDequeueMessage(), nullptr);
}

TEST_F(LimitedSizeListenerFixture, GetMessages5) {
    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessage>();
    LimitedSizeMessageListener<3> listener(typeId);

    MessagePtr message1 = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>()
    );

    MessagePtr message2 = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessageContainer>()
    );

    MessagePtr message3 = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessageContainer>()
    );

    MessagePtr message4 = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessageContainer>()
    );

    listener.enqueueMessage(message1);
    listener.enqueueMessage(message2);
    listener.enqueueMessage(message3);
    listener.enqueueMessage(message4);
    ASSERT_TRUE(message1.unique());
    ASSERT_EQ(listener.tryDequeueMessage(), message2);
    ASSERT_EQ(listener.tryDequeueMessage(), message3);
    ASSERT_EQ(listener.tryDequeueMessage(), message4);
    ASSERT_EQ(listener.tryDequeueMessage(), nullptr);
}