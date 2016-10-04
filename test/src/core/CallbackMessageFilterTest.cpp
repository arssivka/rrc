/**
 * @author arssivka
 * @date 9/30/16
 */

#include <gtest/gtest.h>
#include <rrc/core/Message.h>
#include <Message.pb.h>
#include <rrc/core/CallbackMessageFilter.h>

using namespace rrc;


class CallbackMessageFilterFixture : public ::testing::Test {
public:
    CallbackMessageFilterFixture() {
        mMetaTable.registerTypeId<testmessages::TestMessage>(1);
        mMetaTable.registerTypeId<testmessages::TestMessageContainer>(2);

    }

protected:
    MetaTable mMetaTable;
};


TEST_F(CallbackMessageFilterFixture, AcceptedMessageTest) {
    testmessages::TestMessage tstMessage;
    tstMessage.set_id(42);
    tstMessage.set_txt("42");

    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessage>();
    MessagePtr messagePtr = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>(std::move(tstMessage))
    );

    CallbackMessageFilter filter([=](MessagePtr message) {
        if (message->getTypeId() == typeId) {
            auto testMessage = (const testmessages::TestMessage*) message->getData();
            return testMessage->id() == 42;
        }
        return false;
    });
    EXPECT_TRUE(filter.accept(messagePtr));
}


TEST_F(CallbackMessageFilterFixture, RejectedMessageTest1) {
    testmessages::TestMessage tstMessage;
    tstMessage.set_id(41);
    tstMessage.set_txt("42");

    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessage>();
    MessagePtr messagePtr = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>(std::move(tstMessage))
    );

    CallbackMessageFilter filter([=](MessagePtr message) {
        if (message->getTypeId() == typeId) {
            auto testMessage = (const testmessages::TestMessage*) message->getData();
            return testMessage->id() == 42;
        }
        return false;
    });
    EXPECT_FALSE(filter.accept(messagePtr));
}


TEST_F(CallbackMessageFilterFixture, RejectedMessageTest2) {
    testmessages::TestMessageContainer tstMessage;

    TypeId typeId = mMetaTable.getTypeId<testmessages::TestMessageContainer>();
    MessagePtr messagePtr = std::make_shared<Message>(
            typeId,
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessageContainer>(std::move(tstMessage))
    );

    CallbackMessageFilter filter([=](MessagePtr message) {
        if (message->getTypeId() == typeId) {
            auto testMessage = (const testmessages::TestMessage*) message->getData();
            return testMessage->id() == 42;
        }
        return false;
    });
    EXPECT_FALSE(filter.accept(messagePtr));
}