///**
// *  @autor tekatod
// *  @date 9/1/16
// */
//#include <iostream>
//#include <gtest/gtest.h>
//#include <rrc/core/Topic.h>
//#include <rrc/core/QueueMessageListener.h>
//#include <rrc/core/RejectMessageFilter.h>
//#include "Message.pb.h"
//
//using namespace rrc;
//
//class TopicFixture : public ::testing::Test {
//public:
//    TopicFixture() : mFirstMessageListenerPtr(std::make_shared<QueueMessageListener>(1u)),
//                        mSecondMessageListenerPtr(std::make_shared<QueueMessageListener>(2u)) {
//        mMetaTable.registerTypeId<testmessages::TestMessage>(1u);
//        mMetaTable.registerTypeId<testmessages::TestMessageContainer>(2u);
//
//    }
//
//    ~TopicFixture() {
//        //Destroy all the good members
//    }
//
//protected:
//    QueueMessageListenerPtr mFirstMessageListenerPtr;
//    QueueMessageListenerPtr mSecondMessageListenerPtr;
//    MetaTable mMetaTable;
//};
//
//
//TEST_F(TopicFixture, EmptyTrueTest) {
//    Topic tstTopic;
//    EXPECT_FALSE(tstTopic.hasListeners());
//    tstTopic.addListener(mFirstMessageListenerPtr);
//    EXPECT_TRUE(tstTopic.hasListeners());
//}
//
//
//TEST_F(TopicFixture, RemoveTest) {
//    Topic tstTopic;
//    tstTopic.addListener(mFirstMessageListenerPtr);
//    tstTopic.removeListener(mFirstMessageListenerPtr);
//    EXPECT_FALSE(tstTopic.hasListeners());
//}
//
//TEST_F(TopicFixture, SendTest1) {
//    Topic tstTopic;
//    tstTopic.addListener(mFirstMessageListenerPtr);
//    testmessages::TestMessage tstMessage;
//    tstMessage.set_id(42);
//    tstMessage.set_txt("42");
//
//    MessagePtr messagePtr = std::make_shared<Message>(
//            mMetaTable.getTypeId<testmessages::TestMessage>(),
//            std::chrono::steady_clock::now(),
//            std::make_unique<testmessages::TestMessage>(std::move(tstMessage))
//    );
//
//    tstTopic.sendMessage(messagePtr);
//    EXPECT_NE(mFirstMessageListenerPtr->tryDequeueMessage(), nullptr);
//    EXPECT_EQ(mFirstMessageListenerPtr->tryDequeueMessage(), nullptr);
//
//    MessagePtr messagePtr2 = std::make_shared<Message>(
//            mMetaTable.getTypeId<testmessages::TestMessageContainer>(),
//            std::chrono::steady_clock::now(),
//            std::make_unique<testmessages::TestMessage>(tstMessage)
//    );
//
//    tstTopic.sendMessage(messagePtr2);
//    EXPECT_EQ(mFirstMessageListenerPtr->tryDequeueMessage(), nullptr);
//}
//
//
//TEST_F(TopicFixture, SendTest2) {
//    Topic tstTopic;
//    tstTopic.setMessageFilter(std::make_shared<RejectMessageFilter>());
//    tstTopic.addListener(mFirstMessageListenerPtr);
//    testmessages::TestMessage tstMessage;
//    tstMessage.set_id(42);
//    tstMessage.set_txt("42");
//
//    MessagePtr messagePtr = std::make_shared<Message>(
//            mMetaTable.getTypeId<testmessages::TestMessage>(),
//            std::chrono::steady_clock::now(),
//            std::make_unique<testmessages::TestMessage>(std::move(tstMessage))
//    );
//
//    tstTopic.sendMessage(messagePtr);
//    EXPECT_EQ(mFirstMessageListenerPtr->tryDequeueMessage(), nullptr);
//    EXPECT_EQ(mFirstMessageListenerPtr->tryDequeueMessage(), nullptr);
//
//    MessagePtr messagePtr2 = std::make_shared<Message>(
//            mMetaTable.getTypeId<testmessages::TestMessageContainer>(),
//            std::chrono::steady_clock::now(),
//            std::make_unique<testmessages::TestMessage>(tstMessage)
//    );
//
//    tstTopic.sendMessage(messagePtr2);
//    EXPECT_EQ(mFirstMessageListenerPtr->tryDequeueMessage(), nullptr);
//}
//
//
//TEST_F(TopicFixture, SendTest3) {
//    Topic tstTopic;
//    tstTopic.setMessageFilter(std::make_shared<RejectMessageFilter>());
//    tstTopic.setMessageFilterEnabled(false);
//    tstTopic.addListener(mFirstMessageListenerPtr);
//    testmessages::TestMessage tstMessage;
//    tstMessage.set_id(42);
//    tstMessage.set_txt("42");
//
//    MessagePtr messagePtr = std::make_shared<Message>(
//            mMetaTable.getTypeId<testmessages::TestMessage>(),
//            std::chrono::steady_clock::now(),
//            std::make_unique<testmessages::TestMessage>(std::move(tstMessage))
//    );
//
//    tstTopic.sendMessage(messagePtr);
//    EXPECT_EQ(mFirstMessageListenerPtr->tryDequeueMessage(), nullptr);
//    EXPECT_EQ(mFirstMessageListenerPtr->tryDequeueMessage(), nullptr);
//
//    MessagePtr messagePtr2 = std::make_shared<Message>(
//            mMetaTable.getTypeId<testmessages::TestMessageContainer>(),
//            std::chrono::steady_clock::now(),
//            std::make_unique<testmessages::TestMessage>(tstMessage)
//    );
//
//    tstTopic.sendMessage(messagePtr2);
//    EXPECT_EQ(mFirstMessageListenerPtr->tryDequeueMessage(), nullptr);
//}
//
//
//TEST_F(TopicFixture, AutoremoveGetterAndSetter) {
//    Topic tstTopic;
//    EXPECT_TRUE(tstTopic.isAutoRemoveEnabled());
//    tstTopic.setAutoRemoveEnabled(false);
//    EXPECT_FALSE(tstTopic.isAutoRemoveEnabled());
//    tstTopic.setAutoRemoveEnabled(true);
//    EXPECT_TRUE(tstTopic.isAutoRemoveEnabled());
//}
//
//
//TEST_F(TopicFixture, FilterEnabledGetterAndSetter) {
//    Topic tstTopic;
//    EXPECT_TRUE(tstTopic.isMessageFilterEnabled());
//    tstTopic.setMessageFilterEnabled(false);
//    EXPECT_FALSE(tstTopic.isMessageFilterEnabled());
//    tstTopic.setMessageFilterEnabled(true);
//    EXPECT_TRUE(tstTopic.isMessageFilterEnabled());
//}
//
//
//TEST_F(TopicFixture, FilterGetterAndSetter) {
//    Topic tstTopic;
//    auto filter = std::make_shared<RejectMessageFilter>();
//    EXPECT_EQ(dynamic_cast<RejectMessageFilter*>(tstTopic.getMessageFilter().get()), nullptr);
//    tstTopic.setMessageFilter(filter);
//    EXPECT_EQ(tstTopic.getMessageFilter(), filter);
//}