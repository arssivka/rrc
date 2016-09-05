/**
 *  @autor tekatod
 *  @date 9/2/16
 */
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/core/ReceiveGuard.h"
#include "Message.pb.h"

using namespace rrc;

class RecieveGuardFixture : public ::testing::Test {
public:
    RecieveGuardFixture() {
        testmessages::TestMessage tstMessage;
        tstMessage.set_id(42);
        tstMessage.set_txt("42");
        mTimePoint = std::chrono::steady_clock::now();
        mMetaTable.registerTypeId<testmessages::TestMessage>(1u);
        mMetaTable.registerTypeId<testmessages::TestMessageContainer>(2u);
        mMessage = std::make_shared<Message>(mMetaTable.getTypeId<testmessages::TestMessage>(), mTimePoint,
                                                          std::make_unique<testmessages::TestMessage>(tstMessage));
    }

    ~RecieveGuardFixture() {

    }

protected:
    MetaTable mMetaTable;
    MessagePtr mMessage;
    std::chrono::steady_clock::time_point mTimePoint;
};


TEST_F(RecieveGuardFixture, ExceptionTest) {
    EXPECT_THROW(ReceiveGuard<testmessages::TestMessage> receiveGuard(mMessage, 3u), IncompatibleTypesException);
}


TEST_F(RecieveGuardFixture, getTypeIdTest) {
    ReceiveGuard<testmessages::TestMessage> receiveGuard(mMessage, 1u);
    EXPECT_EQ(receiveGuard.getTypeId(), mMetaTable.getTypeId<testmessages::TestMessage>());
}


TEST_F(RecieveGuardFixture, getTimestampTest) {
    ReceiveGuard<testmessages::TestMessage> receiveGuard(mMessage, 1u);
    EXPECT_EQ(receiveGuard.getTimestamp(), mTimePoint);
}


TEST_F(RecieveGuardFixture, isSetTest) {
    ReceiveGuard<testmessages::TestMessage> receiveGuard(mMessage, 1u);
    EXPECT_TRUE(receiveGuard.isMessageSet());
    ReceiveGuard<testmessages::TestMessage> receiveGuard2(nullptr, 1u);
    EXPECT_FALSE(receiveGuard2.isMessageSet());
}


TEST_F(RecieveGuardFixture, getDataTest) {
    ReceiveGuard<testmessages::TestMessage> receiveGuard(mMessage, 1u);
    EXPECT_EQ(receiveGuard.getData()->id(), ((testmessages::TestMessage*)mMessage->getData())->id());
    EXPECT_EQ(receiveGuard.getData()->txt(), ((testmessages::TestMessage*)mMessage->getData())->txt());
}


TEST_F(RecieveGuardFixture, operatorArrowTest) {
    ReceiveGuard<testmessages::TestMessage> receiveGuard(mMessage, 1u);
    EXPECT_EQ(receiveGuard->id(), ((testmessages::TestMessage*)mMessage->getData())->id());
    EXPECT_EQ(receiveGuard->txt(), ((testmessages::TestMessage*)mMessage->getData())->txt());
}