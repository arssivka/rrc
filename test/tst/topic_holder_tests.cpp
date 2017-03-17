/**
 *  @autor arssivka
 *  @date 3/13/17
 */


#include <gtest/gtest.h>
#include <rrc/rrc.h>
#include <flag_setter.h>

using namespace rrc;

class topic_holder_fixture : public ::testing::Test {
protected:
    void SetUp() override {
        m_flag1 = false;
        m_flag2 = false;
        m_message = shared_buffer("flaceh");
        m_callback1 = topic_callback([this](const shared_buffer& msg) {
            m_flag1 = msg == m_message;
        });
        m_callback2 = topic_callback([this](const shared_buffer& msg) {
            m_flag2 = msg == m_message;
        });
    }


protected:
    bool m_flag1;
    bool m_flag2;
    shared_buffer m_message;
    topic_callback m_callback1;
    topic_callback m_callback2;
    topic_holder m_holder;
};


TEST_F(topic_holder_fixture, add_listener) {
    EXPECT_TRUE(m_callback1.unique());
    EXPECT_TRUE(m_callback2.unique());
    m_holder.add_topic_listener("topic!", m_callback1);
    EXPECT_FALSE(m_callback1.unique());
    EXPECT_TRUE(m_callback2.unique());
    m_holder.add_topic_listener("topic!", m_callback2);
    EXPECT_FALSE(m_callback1.unique());
    EXPECT_FALSE(m_callback2.unique());
}

TEST_F(topic_holder_fixture, remove_listener) {
    EXPECT_TRUE(m_callback1.unique());
    EXPECT_TRUE(m_callback2.unique());
    m_holder.add_topic_listener("topic!", m_callback1);
    m_holder.add_topic_listener("topic!", m_callback2);
    EXPECT_FALSE(m_callback1.unique());
    EXPECT_FALSE(m_callback2.unique());
    m_holder.remove_topic_listener("topic!", m_callback1);
    m_holder.remove_topic_listener("topic!", m_callback2);
    EXPECT_TRUE(m_callback1.unique());
    EXPECT_TRUE(m_callback2.unique());
}

TEST_F(topic_holder_fixture, send_message) {
    m_holder.add_topic_listener("topic!", m_callback1);
    m_holder.add_topic_listener("topic!", m_callback2);
    EXPECT_FALSE(m_flag1);
    EXPECT_FALSE(m_flag2);
    m_holder.send_message("topic", m_message);
    EXPECT_FALSE(m_flag1);
    EXPECT_FALSE(m_flag2);
    m_holder.send_message("topic!", m_message);
    EXPECT_TRUE(m_flag1);
    EXPECT_TRUE(m_flag2);
}

TEST_F(topic_holder_fixture, keys) {
    EXPECT_TRUE(m_holder.keys().empty());
    m_holder.add_topic_listener("topic!", m_callback1);
    m_holder.add_topic_listener("topic!", m_callback2);
    EXPECT_EQ(m_holder.keys(), std::vector<std::string>{"topic!"});
    m_holder.add_topic_listener("topic", m_callback1);
    std::vector<std::string> vector1{"topic", "topic!"};
    EXPECT_EQ(m_holder.keys(), vector1);
    m_holder.remove_topic_listener("topic!", m_callback1);
    EXPECT_EQ(m_holder.keys(), vector1);
    m_holder.remove_topic_listener("topic!", m_callback2);
    EXPECT_EQ(m_holder.keys(), std::vector<std::string>{"topic"});

}