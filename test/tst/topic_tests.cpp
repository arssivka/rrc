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
    using subscriber_type = typename topic<std::string>::callback_type;

    void SetUp() override {
        m_send_flag = false;
        m_test_message = std::string("meow!");
        m_listener = std::make_shared<subscriber_type>([this](std::string message) {
            m_last_message = message;
            m_send_flag = true;
        });
    }

protected:
    std::string m_test_message;
    std::string m_last_message;
    bool m_send_flag;
    std::shared_ptr<subscriber_type> m_listener;

};

TEST_F(topic_fixture, has_listener) {
    topic<std::string> tpc;
    EXPECT_FALSE(tpc.has_listeners());
    tpc.add_listener(m_listener);
    EXPECT_TRUE(tpc.has_listeners());
    tpc.add_listener(m_listener);
    EXPECT_TRUE(tpc.has_listeners());
    tpc.remove_listener(m_listener);
    EXPECT_FALSE(tpc.has_listeners());
}


TEST_F(topic_fixture, add_listener) {
    topic<std::string> tpc;
    EXPECT_FALSE(tpc.has_listeners());
    tpc.add_listener(m_listener);
    EXPECT_TRUE(tpc.has_listeners());
}


TEST_F(topic_fixture, remove_listener) {
    topic<std::string> tpc;
    EXPECT_FALSE(tpc.has_listeners());
    tpc.add_listener(m_listener);
    tpc.add_listener(m_listener);
    tpc.remove_listener(m_listener);
    EXPECT_FALSE(tpc.has_listeners());
}


TEST_F(topic_fixture, send_1) {
    topic<std::string> tpc;
    EXPECT_FALSE(m_send_flag);
    tpc.send_message(m_test_message);
    EXPECT_FALSE(m_send_flag);
    tpc.add_listener(m_listener);
    tpc.send_message(m_test_message);
    EXPECT_TRUE(m_send_flag);
    EXPECT_EQ(m_last_message, m_test_message);
}