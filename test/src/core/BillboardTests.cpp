/**
 *  @autor tekatod
 *  @date 9/2/16
 */
#include <string>
#include <gtest/gtest.h>
#include "rrc/core/TopicHolder.h"
#include "Message.pb.h"

using namespace rrc;

class BillboardFixture : public ::testing::Test {
public:
    BillboardFixture() {
        mMetaTable.registerTypeId<testmessages::TestMessage>(1u);
        mMetaTable.registerTypeId<testmessages::TestMessageContainer>(2u);
    }

protected:
    MetaTable mMetaTable;

};


TEST_F(BillboardFixture, CreateAndGetTopicTest) {
    TopicHolder<std::string> billboard;
    billboard.createTopic("TestTopic");
    billboard.createTopic("TestTopic2");
    EXPECT_NE(billboard.getTopic("TestTopic"), nullptr);
    EXPECT_NE(billboard.getTopic("TestTopic2"), nullptr);
    EXPECT_EQ(billboard.getTopic("TestTopic3"), nullptr);
}


TEST_F(BillboardFixture, RemoveTest) {
    TopicHolder<std::string> billboard;
    billboard.createTopic("TestTopic");
    billboard.createTopic("TestTopic2");
    billboard.removeTopic("TestTopic");
    billboard.removeTopic("TestTopic2");
    EXPECT_EQ(billboard.getTopic("TestTopic"), nullptr);
    EXPECT_EQ(billboard.getTopic("TestTopic2"), nullptr);
}

TEST_F(BillboardFixture, GetKeysTest) {
    TopicHolder<std::string> billboard;
    billboard.createTopic("TestTopic");
    billboard.createTopic("TestTopic2");
    auto testKeys = billboard.getTopicNames();
    EXPECT_NE(std::find(testKeys.begin(), testKeys.end(), "TestTopic"), testKeys.end());
    EXPECT_NE(std::find(testKeys.begin(), testKeys.end(), "TestTopic2"), testKeys.end());
    EXPECT_EQ(std::find(testKeys.begin(), testKeys.end(), "TestTopic3"), testKeys.end());
}