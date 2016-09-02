/**
 *  @autor tekatod
 *  @date 9/1/16
 */
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/Topic.h"
#include "Message.pb.h"

class ListenerFixture : public ::testing::Test {
public:
    ListenerFixture() : mRightML(std::make_shared<rrc::MessageListener>(1)),
                        mWrongML(std::make_shared<rrc::MessageListener>(2)) {

    }
    ~ListenerFixture() {
        //Destroy all the good members
    }
    rrc::MessageListenerPtr mRightML;
    rrc::MessageListenerPtr mWrongML;
};

TEST_F(ListenerFixture, RightTypeAddListenerTest) {
    rrc::Topic tstTopic(1);
    EXPECT_TRUE(tstTopic.addListener(mRightML));
}

TEST_F(ListenerFixture, WrongTypeAddListenerTest) {
    rrc::Topic tstTopic(1);
    EXPECT_FALSE(tstTopic.addListener(mWrongML));
}

//TEST_F(ListenerFixture, WrongTypeAddListenerTest) {
//    rrc::Topic tstTopic(1);
//    EXPECT_FALSE(tstTopic.addListener(mWrongML));
//}