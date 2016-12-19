///**
// * @author arssivka
// * @date 9/30/16
// */
//
//#include <gtest/gtest.h>
//#include <rrc/core/Message.h>
//#include <Message.pb.h>
//#include <rrc/core/TypeIdMessageFilter.h>
//
//using namespace rrc;
//
//
//class TypeIdMessageFilterFixture : public ::testing::Test {
//public:
//    TypeIdMessageFilterFixture() {
//        mMetaTable.registerTypeId<testmessages::TestMessage>(1);
//        mMetaTable.registerTypeId<testmessages::TestMessageContainer>(2);
//
//    }
//
//protected:
//    MetaTable mMetaTable;
//};
//
//
//TEST_F(TypeIdMessageFilterFixture, AcceptedMessageTest) {
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
//    TypeIdMessageFilter filter(mMetaTable.getTypeId<testmessages::TestMessage>());
//    EXPECT_TRUE(filter.accept(messagePtr));
//}
//
//
//TEST_F(TypeIdMessageFilterFixture, RejectedMessageTest1) {
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
//    TypeIdMessageFilter filter(mMetaTable.getTypeId<testmessages::TestMessageContainer>());
//    EXPECT_FALSE(filter.accept(messagePtr));
//}
//
//
//TEST_F(TypeIdMessageFilterFixture, RejectedMessageTest2) {
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
//    MessagePtr messagePtr2 = std::make_shared<Message>(
//            mMetaTable.getTypeId<testmessages::TestMessageContainer>(),
//            std::chrono::steady_clock::now(),
//            std::make_unique<testmessages::TestMessage>(tstMessage)
//    );
//
//    TypeIdMessageFilter filter;
//    EXPECT_FALSE(filter.accept(messagePtr));
//    EXPECT_FALSE(filter.accept(messagePtr2));
//}
//
//
//TEST_F(TypeIdMessageFilterFixture, GetterAndSetterTest) {
//    TypeIdMessageFilter filter;
//    EXPECT_EQ(filter.getTypeId(), MetaTable::UNKNOWN_TYPE_ID);
//    filter.setTypeId(1);
//    EXPECT_EQ(filter.getTypeId(), 1u);
//    filter.setTypeId(3);
//    EXPECT_EQ(filter.getTypeId(), 3u);
//}