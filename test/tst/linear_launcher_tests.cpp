///**
// *  @autor arssivka
// *  @date 9/5/16
// */
//
//#include <gtest/gtest.h>
//#include <rrc/core.h>
//#include <dummy_node.h>
//
//using namespace rrc;
//
//
//class linear_launcher_fixture : public ::testing::Test {
//protected:
//    void SetUp() override {
//        m_sync_queue.reset(new stl_queue_adapter<task>());
//    }
//
//
//protected:
//    std::shared_ptr<abstract_queue_adapter<task>> m_sync_queue;
//};
//
//
//TEST_F(linear_launcher_fixture, add_and_delete_node) {
//    LinearLauncher lockfree_launcher;
//    RootNodePtr rootNode = std::make_shared<RootNode>(lockfree_launcher, mMetaTable, mSettingsHolder);
//    std::shared_ptr<dummy_node> node1 = std::make_shared<dummy_node>(rootNode, "test");
//    std::shared_ptr<dummy_node> node2 = std::make_shared<dummy_node>(rootNode, "test");
//
//    lockfree_launcher.addNode(node1);
//    lockfree_launcher.addNode(node2);
//    EXPECT_FALSE(node1.unique());
//    EXPECT_FALSE(node2.unique());
//    lockfree_launcher.removeNode(node2);
//    EXPECT_FALSE(node1.unique());
//    EXPECT_TRUE(node2.unique());
//    lockfree_launcher.removeNode(node1);
//    EXPECT_TRUE(node1.unique());
//    EXPECT_TRUE(node2.unique());
//}
//
//
//TEST_F(linear_launcher_fixture, Step) {
//    LinearLauncher lockfree_launcher;
//    RootNodePtr rootNode = std::make_shared<RootNode>(lockfree_launcher, mMetaTable, mSettingsHolder);
//    lockfree_launcher.setRootNode(rootNode);
//    std::shared_ptr<dummy_node> node1 = std::make_shared<dummy_node>(rootNode, "test");
//    std::shared_ptr<dummy_node> node2 = std::make_shared<dummy_node>(rootNode, "test");
//    lockfree_launcher.addNode(node1);
//    lockfree_launcher.addNode(node2);
//    EXPECT_EQ(node1->getCounter(), 0);
//    EXPECT_EQ(node2->getCounter(), 0);
//    EXPECT_TRUE(lockfree_launcher.step());
//    EXPECT_EQ(node1->getCounter(), 1);
//    EXPECT_EQ(node2->getCounter(), 1);
//    EXPECT_TRUE(lockfree_launcher.step());
//    EXPECT_EQ(node1->getCounter(), 2);
//    EXPECT_EQ(node2->getCounter(), 2);
//    EXPECT_TRUE(lockfree_launcher.step());
//    EXPECT_EQ(node1->getCounter(), 3);
//    EXPECT_EQ(node2->getCounter(), 3);
//    EXPECT_TRUE(lockfree_launcher.step());
//    EXPECT_EQ(node1->getCounter(), 4);
//    EXPECT_EQ(node2->getCounter(), 4);
//    EXPECT_TRUE(lockfree_launcher.step());
//    EXPECT_EQ(node1->getCounter(), 5);
//    EXPECT_EQ(node2->getCounter(), 5);
//    EXPECT_FALSE(lockfree_launcher.step());
//}