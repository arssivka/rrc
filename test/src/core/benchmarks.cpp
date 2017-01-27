/**
 *  @autor tekatod
 *  @date 10/5/16
 */
#include <gtest/gtest.h>
#include <rrc/core/LinearLauncher.h>
#include <rrc/core/RootNode.h>
#include <Message.pb.h>
#include <rrc/core/RejectMessageFilter.h>
#include <rrc/core/SettingsHolder.h>
#include "include/DummyNode.h"

using namespace rrc;

class BenchMarkFixture : public ::testing::Test {
public:
    BenchMarkFixture() : mSettingsHolder()   {
        mMetaTable.registerTypeId<testmessages::TestMessage>(0);
        mMetaTable.registerTypeId<testmessages::TestMessageContainer>(1);
        mRootNode = std::make_shared<RootNode>(mLinearLauncher, mMetaTable, mSettingsHolder);
    }

protected:
    MetaTable mMetaTable;
    LinearLauncher mLinearLauncher;
    RootNodePtr mRootNode;
    SettingsHolder mSettingsHolder;
};

TEST_F(BenchMarkFixture, QueueMessageListenerTest) {
//    std::shared_ptr<DummyNode> dummyNode1 = std::make_shared<DummyNode>(mRootNode, "test");
    std::vector<std::shared_ptr<DummyNode>> nodes;
    for(int i = 0; i < 1000; ++i) {
        nodes.push_back(std::make_shared<DummyNode>(mRootNode, "test"));
    }
    testmessages::TestMessage tstMessage;
    tstMessage.set_id(42);
    tstMessage.set_txt("42");

//    MessagePtr message1 = std::make_shared<Message>(
//            mMetaTable.getTypeId<testmessages::TestMessage>(),
//            std::chrono::steady_clock::now(),
//            std::make_unique<testmessages::TestMessage>(tstMessage)
//    );
    for (int i = 0; i < 100000; ++i) {
        mRootNode->sendMessage("test", std::make_shared<Message>(
                mMetaTable.getTypeId<testmessages::TestMessage>(),
                std::chrono::steady_clock::now(),
                std::make_unique<testmessages::TestMessage>(tstMessage)
        ));
    }

    mRootNode->entry();
    EXPECT_TRUE(true);
}