/**
 *  @autor arssivka
 *  @date 9/5/16
 */

#include <gtest/gtest.h>
#include <rrc/core.h>
#include <dummy_node.h>

using namespace rrc;


class LinearLauncherFixture : public ::testing::Test {
public:
    LinearLauncherFixture() {
        mMetaTable.registerTypeId<testmessages::TestMessage>(0);
    }

protected:
    MetaTable mMetaTable;
    SettingsHolder mSettingsHolder;
};


TEST_F(LinearLauncherFixture, AddAndDeleteTest) {
    LinearLauncher launcher;
    RootNodePtr rootNode = std::make_shared<RootNode>(launcher, mMetaTable, mSettingsHolder);
    std::shared_ptr<dummy_node> node1 = std::make_shared<dummy_node>(rootNode, "test");
    std::shared_ptr<dummy_node> node2 = std::make_shared<dummy_node>(rootNode, "test");

    launcher.addNode(node1);
    launcher.addNode(node2);
    EXPECT_FALSE(node1.unique());
    EXPECT_FALSE(node2.unique());
    launcher.removeNode(node2);
    EXPECT_FALSE(node1.unique());
    EXPECT_TRUE(node2.unique());
    launcher.removeNode(node1);
    EXPECT_TRUE(node1.unique());
    EXPECT_TRUE(node2.unique());
}


TEST_F(LinearLauncherFixture, Step) {
    LinearLauncher launcher;
    RootNodePtr rootNode = std::make_shared<RootNode>(launcher, mMetaTable, mSettingsHolder);
    launcher.setRootNode(rootNode);
    std::shared_ptr<dummy_node> node1 = std::make_shared<dummy_node>(rootNode, "test");
    std::shared_ptr<dummy_node> node2 = std::make_shared<dummy_node>(rootNode, "test");
    launcher.addNode(node1);
    launcher.addNode(node2);
    EXPECT_EQ(node1->getCounter(), 0);
    EXPECT_EQ(node2->getCounter(), 0);
    EXPECT_TRUE(launcher.step());
    EXPECT_EQ(node1->getCounter(), 1);
    EXPECT_EQ(node2->getCounter(), 1);
    EXPECT_TRUE(launcher.step());
    EXPECT_EQ(node1->getCounter(), 2);
    EXPECT_EQ(node2->getCounter(), 2);
    EXPECT_TRUE(launcher.step());
    EXPECT_EQ(node1->getCounter(), 3);
    EXPECT_EQ(node2->getCounter(), 3);
    EXPECT_TRUE(launcher.step());
    EXPECT_EQ(node1->getCounter(), 4);
    EXPECT_EQ(node2->getCounter(), 4);
    EXPECT_TRUE(launcher.step());
    EXPECT_EQ(node1->getCounter(), 5);
    EXPECT_EQ(node2->getCounter(), 5);
    EXPECT_FALSE(launcher.step());
}