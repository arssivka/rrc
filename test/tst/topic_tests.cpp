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
        m_test_message = string("meow!");
        m_listener = topic_callback([this](const string& message) {
            m_last_message = message;
            m_send_flag = true;
        });
    }

protected:
    string m_test_message;
    string m_last_message;
    bool m_send_flag;
    topic_callback m_listener;

};

TEST_F(topic_fixture, has_listener) {
    topic tpc;
    EXPECT_EQ(tpc.listeners_count(), 0u);
    tpc.add_listener(m_listener);
    EXPECT_EQ(tpc.listeners_count(), 1u);
    tpc.add_listener(m_listener);
    EXPECT_EQ(tpc.listeners_count(), 1u);
    tpc.remove_listener(m_listener);
    EXPECT_EQ(tpc.listeners_count(), 0u);
}


TEST_F(topic_fixture, add_listener) {
    topic tpc;
    EXPECT_EQ(tpc.listeners_count(), 0u);
    tpc.add_listener(m_listener);
    EXPECT_EQ(tpc.listeners_count(), 1u);
}


TEST_F(topic_fixture, remove_listener) {
    topic tpc;
    EXPECT_EQ(tpc.listeners_count(), 0u);
    tpc.add_listener(m_listener);
    tpc.add_listener(m_listener);
    tpc.remove_listener(m_listener);
    EXPECT_EQ(tpc.listeners_count(), 0u);
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