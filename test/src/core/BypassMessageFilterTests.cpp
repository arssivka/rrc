/**
 * @author arssivka
 * @date 9/30/16
 */


#include <gtest/gtest.h>
#include <rrc/core/Message.h>
#include <Message.pb.h>
#include <rrc/core/BypassMessageFilter.h>

using namespace rrc;


class BypassMessageFilterFixture : public ::testing::Test {
public:
    BypassMessageFilterFixture() {
        mMetaTable.registerTypeId<testmessages::TestMessage>(1);
        mMetaTable.registerTypeId<testmessages::TestMessageContainer>(2);

    }

protected:
    MetaTable mMetaTable;
};


TEST_F(BypassMessageFilterFixture, RejectedMessageTest) {
    testmessages::TestMessage tstMessage;
    tstMessage.set_id(42);
    tstMessage.set_txt("42");

    MessagePtr messagePtr = std::make_shared<Message>(
            mMetaTable.getTypeId<testmessages::TestMessage>(),
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>(std::move(tstMessage))
    );

    MessagePtr messagePtr2 = std::make_shared<Message>(
            mMetaTable.getTypeId<testmessages::TestMessageContainer>(),
            std::chrono::steady_clock::now(),
            std::make_unique<testmessages::TestMessage>(tstMessage)
    );

    BypassMessageFilter filter;
    EXPECT_TRUE(filter.accept(messagePtr));
    EXPECT_TRUE(filter.accept(messagePtr2));
}