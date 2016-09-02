///**
// *  @autor tekatod
// *  @date 9/1/16
// */
//
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/Message.h"
#include "Message.pb.h"

TEST(MessageTest, GetMessageTest) {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    message::TestMessage pbmsg;
    pbmsg.set_id(42);
    pbmsg.set_txt("42");
    rrc::Message tstMsg(1, now, std::make_unique<message::TestMessage>(pbmsg));
    const message::TestMessage* pbmsg2 =  (message::TestMessage*)tstMsg.getData();
    EXPECT_TRUE(pbmsg.id() == pbmsg2->id() && pbmsg.txt() == pbmsg2->txt());
}

TEST(MessageTest, GetDataFromMessageTest) {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    message::TestMessage pbmsg;
    pbmsg.set_id(42);
    pbmsg.set_txt("42");
    rrc::Message tstMsg(1, now, std::make_unique<message::TestMessage>(pbmsg));
    EXPECT_TRUE(pbmsg.id() == ((message::TestMessage*)tstMsg.getData())->id() &&
                        pbmsg.txt() == ((message::TestMessage*)tstMsg.getData())->txt());
}