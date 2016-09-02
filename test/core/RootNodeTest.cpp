/**
 *  @autor arssivka
 *  @date 9/2/16
 */

#include <gtest/gtest.h>
#include <rrc/LinearLauncher.h>
#include <rrc/RootNode.h>
#include <Message.pb.h>
#include "DummyNode.h"

using namespace rrc;


class RootNodeFixture : public ::testing::Test {
public:
    RootNodeFixture() {
        mMetaTable.registerTypeId<message::TestMessage>(0);
        mMetaTable.registerTypeId<message::TestMessageContainer>(1);
    }

protected:
    MetaTable mMetaTable;
    LinearLauncher mLinearLauncher;

};


TEST_F(RootNodeFixture, AddAndRemoveListenerTest1) {
    RootNodePtr rootNode = std::make_shared<RootNode>(&mLinearLauncher, &mMetaTable);
    TypeId typeId = mMetaTable.getTypeId<message::TestMessage>();
    MessageListenerPtr listener = std::make_shared<MessageListener>(typeId);
    rootNode->addListener("test", listener);
    rootNode->entry();
    EXPECT_FALSE(listener.unique());
    rootNode->removeListener("test", listener);
    EXPECT_FALSE(listener.unique());
    rootNode->entry();
    EXPECT_TRUE(listener.unique());
}


TEST_F(RootNodeFixture, AddAndRemoveListenerTest2) {
    RootNodePtr rootNode = std::make_shared<RootNode>(&mLinearLauncher, &mMetaTable);
    TypeId typeId = mMetaTable.getTypeId<message::TestMessage>();
    MessageListenerPtr listener = std::make_shared<MessageListener>(typeId);
    rootNode->addListener("test", listener);
    EXPECT_FALSE(listener.unique());
    rootNode->removeListener("test", listener);
    EXPECT_FALSE(listener.unique());
    rootNode->entry();
    EXPECT_TRUE(listener.unique());
}


TEST_F(RootNodeFixture, AddAndRemoveNodeTest3) {
    RootNodePtr rootNode = std::make_shared<RootNode>(&mLinearLauncher, &mMetaTable);
    std::shared_ptr<DummyNode> dummyNode = std::make_shared<DummyNode>(rootNode, "test");
    rootNode->addNode(dummyNode);
    EXPECT_FALSE(dummyNode.unique());
    rootNode->removeNode(dummyNode);
    EXPECT_FALSE(dummyNode.unique());
    rootNode->entry();
    EXPECT_TRUE(dummyNode.unique());
}


TEST_F(RootNodeFixture, GetTypeIdTest) {
    MetaTable metaTable;
    metaTable.registerTypeId<message::TestMessage>(0u);
    RootNodePtr rootNode = std::make_shared<RootNode>(&mLinearLauncher, &metaTable);
    EXPECT_EQ(rootNode->getTypeId<message::TestMessage>(), 0u);
    EXPECT_EQ(rootNode->getTypeId<message::TestMessageContainer>(), MetaTable::UNKNOWN_TYPE_ID);
}


TEST_F(RootNodeFixture, SendMessage1) {
    RootNodePtr rootNode = std::make_shared<RootNode>(&mLinearLauncher, &mMetaTable);
    std::shared_ptr<DummyNode> dummyNode1 = std::make_shared<DummyNode>(rootNode, "test");
    std::shared_ptr<DummyNode> dummyNode2 = std::make_shared<DummyNode>(rootNode, "test");

    message::TestMessage tstMessage;
    tstMessage.set_id(42);
    tstMessage.set_txt("42");

    MessagePtr message1 = std::make_shared<Message>(
            mMetaTable.getTypeId<message::TestMessage>(),
            std::chrono::steady_clock::now(),
            std::make_unique<message::TestMessage>(tstMessage)
    );

    MessagePtr message2 = std::make_shared<Message>(
            mMetaTable.getTypeId<message::TestMessageContainer>(),
            std::chrono::steady_clock::now(),
            std::make_unique<message::TestMessageContainer>()
    );

    rootNode->sendMessage("test", message1);
    rootNode->sendMessage("test", message2);

    rootNode->entry();
    EXPECT_EQ(dummyNode1->tryGetMessage(), message1);
    EXPECT_EQ(dummyNode1->tryGetMessage(), nullptr);
    EXPECT_EQ(dummyNode2->tryGetMessage(), message1);
    EXPECT_EQ(dummyNode2->tryGetMessage(), nullptr);
}