///**
// *  @autor tekatod
// *  @date 9/1/16
// */
//
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/core/Message.h"
#include "Message.pb.h"

TEST(MessageTest, GetMessageTest) {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    testmessages::TestMessage pbmsg;
    pbmsg.set_id(42);
    pbmsg.set_txt("42");
    rrc::Message tstMsg(1, now, std::make_unique<testmessages::TestMessage>(pbmsg));
    const testmessages::TestMessage* pbmsg2 =  (testmessages::TestMessage*)tstMsg.getData();
    EXPECT_TRUE(pbmsg.id() == pbmsg2->id() && pbmsg.txt() == pbmsg2->txt());
}

TEST(MessageTest, GetDataFromMessageTest) {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    testmessages::TestMessage pbmsg;
    pbmsg.set_id(42);
    pbmsg.set_txt("42");
    rrc::Message tstMsg(1, now, std::make_unique<testmessages::TestMessage>(pbmsg));
    EXPECT_TRUE(pbmsg.id() == ((testmessages::TestMessage*)tstMsg.getData())->id() &&
                        pbmsg.txt() == ((testmessages::TestMessage*)tstMsg.getData())->txt());
}