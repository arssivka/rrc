/**
 *  @autor tekatod
 *  @date 9/1/16
 */
#include <iostream>
#include <gtest/gtest.h>
#include <rrc/rrc.h>

using namespace rrc;

class topic_fixture
        : public ::testing::Test {
protected:
    void SetUp() override {
        m_send_flag = false;
        m_test_message = shared_buffer("meow!");
        m_listener = topic_callback([this](const shared_buffer& message) {
            m_last_message = message;
            m_send_flag = true;
        });
    }

protected:
    shared_buffer m_test_message;
    shared_buffer m_last_message;
    bool m_send_flag;
    topic_callback m_listener;

};

TEST_F(topic_fixture, has_listener) {
    topic tpc;
    EXPECT_FALSE(tpc.has_listeners());
    tpc.add_listener(m_listener);
    EXPECT_TRUE(tpc.has_listeners());
    tpc.add_listener(m_listener);
    EXPECT_TRUE(tpc.has_listeners());
    tpc.remove_listener(m_listener);
    EXPECT_FALSE(tpc.has_listeners());
}


TEST_F(topic_fixture, add_listener) {
    topic tpc;
    EXPECT_FALSE(tpc.has_listeners());
    tpc.add_listener(m_listener);
    EXPECT_TRUE(tpc.has_listeners());
}


TEST_F(topic_fixture, remove_listener) {
    topic tpc;
    EXPECT_FALSE(tpc.has_listeners());
    tpc.add_listener(m_listener);
    tpc.add_listener(m_listener);
    tpc.remove_listener(m_listener);
    EXPECT_FALSE(tpc.has_listeners());
}


TEST_F(topic_fixture, send_1) {
    topic tpc;
    EXPECT_FALSE(m_send_flag);
    tpc.send_message(m_test_message);
    EXPECT_FALSE(m_send_flag);
    tpc.add_listener(m_listener);
    tpc.send_message(m_test_message);
    EXPECT_TRUE(m_send_flag);
    EXPECT_EQ(m_last_message, m_test_message);
}