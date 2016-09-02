/**
 *  @autor tekatod
 *  @date 9/2/16
 */
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/ReceiveGuard.h"
#include "Message.pb.h"

using namespace rrc;

class RecieveGuardFixture : public ::testing::Test {
public:
    RecieveGuardFixture() {
        message::TestMessage tstMessage;
        tstMessage.set_id(42);
        tstMessage.set_txt("42");
        mTimePoint = std::chrono::steady_clock::now();
        mMetaTable.registerTypeId<message::TestMessage>(1u);
        mMetaTable.registerTypeId<message::TestMessageContainer>(2u);
        mMessage = std::make_shared<Message>(mMetaTable.getTypeId<message::TestMessage>(), mTimePoint,
                                                          std::make_unique<message::TestMessage>(tstMessage));
    }

    ~RecieveGuardFixture() {

    }

protected:
    MetaTable mMetaTable;
    MessagePtr mMessage;
    std::chrono::steady_clock::time_point mTimePoint;
};


TEST_F(RecieveGuardFixture, ExceptionTest) {
    EXPECT_THROW(ReceiveGuard<message::TestMessage> receiveGuard(mMessage, 3u), IncompatibleTypesException);
}


TEST_F(RecieveGuardFixture, getTypeIdTest) {
    ReceiveGuard<message::TestMessage> receiveGuard(mMessage, 1u);
    EXPECT_EQ(receiveGuard.getTypeId(), mMetaTable.getTypeId<message::TestMessage>());
}


TEST_F(RecieveGuardFixture, getTimestampTest) {
    ReceiveGuard<message::TestMessage> receiveGuard(mMessage, 1u);
    EXPECT_EQ(receiveGuard.getTimestamp(), mTimePoint);
}


TEST_F(RecieveGuardFixture, isSetTest) {
    ReceiveGuard<message::TestMessage> receiveGuard(mMessage, 1u);
    EXPECT_TRUE(receiveGuard.isMessageSet());
    ReceiveGuard<message::TestMessage> receiveGuard2(nullptr, 1u);
    EXPECT_FALSE(receiveGuard2.isMessageSet());
}


TEST_F(RecieveGuardFixture, getDataTest) {
    ReceiveGuard<message::TestMessage> receiveGuard(mMessage, 1u);
    EXPECT_EQ(receiveGuard.getData()->id(), ((message::TestMessage*)mMessage->getData())->id());
    EXPECT_EQ(receiveGuard.getData()->txt(), ((message::TestMessage*)mMessage->getData())->txt());
}


TEST_F(RecieveGuardFixture, operatorArrowTest) {
    ReceiveGuard<message::TestMessage> receiveGuard(mMessage, 1u);
    EXPECT_EQ(receiveGuard->id(), ((message::TestMessage*)mMessage->getData())->id());
    EXPECT_EQ(receiveGuard->txt(), ((message::TestMessage*)mMessage->getData())->txt());
}