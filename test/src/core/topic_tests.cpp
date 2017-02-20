/**
 *  @autor tekatod
 *  @date 9/1/16
 */
#include <iostream>
#include <gtest/gtest.h>
#include <rrc/core/topic.h>
#include <rrc/core/stl_queue_adapter.h>

using namespace rrc;

class topic_fixture
        : public ::testing::Test {
protected:
    using subscriber_type = typename topic::subscriber_type;
    
    void SetUp() override {
        m_send_flag = false;
        m_test_message = make_cow<std::string>("meow!");
        m_task_queue.reset(new stl_queue_adapter<task>());
        m_listener_ptr.reset(new subscriber_type(m_task_queue, [this](cow_string message) {
            m_last_message = message;
            m_send_flag = true;
        }));
    }

protected:
    cow_string m_test_message;
    cow_string m_last_message;
    bool m_send_flag;
    std::shared_ptr<subscriber_type> m_listener_ptr;
    std::shared_ptr<abstract_queue_adapter<task>> m_task_queue;

};

TEST_F(topic_fixture, has_listener) {
    topic tpc;
    EXPECT_FALSE(tpc.has_listeners());
    tpc.add_listener(m_listener_ptr);
    EXPECT_TRUE(tpc.has_listeners());
    tpc.add_listener(m_listener_ptr);
    EXPECT_TRUE(tpc.has_listeners());
    tpc.remove_listener(m_listener_ptr);
    EXPECT_FALSE(tpc.has_listeners());
}


TEST_F(topic_fixture, add_listener) {
    topic tpc;
    EXPECT_FALSE(tpc.has_listeners());
    tpc.add_listener(m_listener_ptr);
    EXPECT_TRUE(tpc.has_listeners());
}


TEST_F(topic_fixture, remove_listener) {
    topic tpc;
    EXPECT_FALSE(tpc.has_listeners());
    tpc.add_listener(m_listener_ptr);
    tpc.add_listener(m_listener_ptr);
    tpc.remove_listener(m_listener_ptr);
    EXPECT_FALSE(tpc.has_listeners());
}


TEST_F(topic_fixture, send_1) {
    topic tpc;
    EXPECT_FALSE(m_send_flag);
    tpc.send_message(m_test_message);
    EXPECT_FALSE(m_send_flag);
    tpc.add_listener(m_listener_ptr);
    tpc.send_message(m_test_message);
    EXPECT_FALSE(m_send_flag);
    exec_once(m_task_queue);
    EXPECT_TRUE(m_send_flag);
    EXPECT_EQ(*m_last_message, *m_test_message);
}


TEST_F(topic_fixture, autoremove) {
    topic tpc;
    tpc.add_listener(m_listener_ptr);
    EXPECT_FALSE(m_send_flag);
    EXPECT_TRUE(tpc.has_listeners());
    m_task_queue = nullptr;
    EXPECT_TRUE(tpc.has_listeners());
    tpc.send_message(m_test_message);
    EXPECT_FALSE(tpc.has_listeners());
    EXPECT_FALSE(m_send_flag);
}