/**
 *  @autor tekatod
 *  @date 9/2/16
 */
#include <string>
#include <gtest/gtest.h>
#include "rrc/core/Billboard.h"
#include "Message.pb.h"

using namespace rrc;

class BillboardFixture : public ::testing::Test {
public:
    BillboardFixture() {
        mMetaTable.registerTypeId<testmessages::TestMessage>(1u);
        mMetaTable.registerTypeId<testmessages::TestMessageContainer>(2u);
    }

    ~BillboardFixture() {
        //Destroy all the good members
    }

protected:
    MetaTable mMetaTable;
};


TEST_F(BillboardFixture, CreateAndGetTopicTest) {
    Billboard<std::string> billboard;
    billboard.createTopic("TestTopic", mMetaTable.getTypeId<testmessages::TestMessage>());
    billboard.createTopic("TestTopic2", mMetaTable.getTypeId<testmessages::TestMessageContainer>());
    EXPECT_NE(billboard.getTopic("TestTopic"), nullptr);
    EXPECT_NE(billboard.getTopic("TestTopic2"), nullptr);
    EXPECT_EQ(billboard.getTopic("TestTopic3"), nullptr);
}


TEST_F(BillboardFixture, RemoveTest) {
    Billboard<std::string> billboard;
    billboard.createTopic("TestTopic", mMetaTable.getTypeId<testmessages::TestMessage>());
    billboard.createTopic("TestTopic2", mMetaTable.getTypeId<testmessages::TestMessageContainer>());
    billboard.removeTopic("TestTopic");
    billboard.removeTopic("TestTopic2");
    EXPECT_EQ(billboard.getTopic("TestTopic"), nullptr);
    EXPECT_EQ(billboard.getTopic("TestTopic2"), nullptr);
}

TEST_F(BillboardFixture, GetKeysTest) {
    Billboard<std::string> billboard;
    billboard.createTopic("TestTopic", mMetaTable.getTypeId<testmessages::TestMessage>());
    billboard.createTopic("TestTopic2", mMetaTable.getTypeId<testmessages::TestMessageContainer>());
    std::set<std::string> testSet = billboard.getKeys();
    EXPECT_NE(testSet.find("TestTopic"), testSet.end());
    EXPECT_NE(testSet.find("TestTopic2"), testSet.end());
    EXPECT_EQ(testSet.find("TestTopic3"), testSet.end());
}