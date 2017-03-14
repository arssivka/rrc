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
    typedef topic_holder<std::string, std::string> holder_type;
    typedef typename holder_type::callback_type callback_type;

    void SetUp() override {
        m_flag1 = false;
        m_flag2 = false;
        m_message = "flaceh";
        m_callback1_ptr = std::make_shared<callback_type>([this](const std::string& msg) {
            m_flag1 = msg == m_message;
        });
        m_callback2_ptr = std::make_shared<callback_type>([this](const std::string& msg) {
            m_flag2 = msg == m_message;
        });
    }


protected:
    bool m_flag1;
    bool m_flag2;
    std::string m_message;
    std::shared_ptr<callback_type> m_callback1_ptr;
    std::shared_ptr<callback_type> m_callback2_ptr;
    holder_type m_holder;
};


TEST_F(topic_holder_fixture, add_listener) {
    EXPECT_TRUE(m_callback1_ptr.unique());
    EXPECT_TRUE(m_callback2_ptr.unique());
    m_holder.add_listener("topic!", m_callback1_ptr);
    EXPECT_FALSE(m_callback1_ptr.unique());
    EXPECT_TRUE(m_callback2_ptr.unique());
    m_holder.add_listener("topic!", m_callback2_ptr);
    EXPECT_FALSE(m_callback1_ptr.unique());
    EXPECT_FALSE(m_callback2_ptr.unique());
}

TEST_F(topic_holder_fixture, remove_listener) {
    EXPECT_TRUE(m_callback1_ptr.unique());
    EXPECT_TRUE(m_callback2_ptr.unique());
    m_holder.add_listener("topic!", m_callback1_ptr);
    m_holder.add_listener("topic!", m_callback2_ptr);
    EXPECT_FALSE(m_callback1_ptr.unique());
    EXPECT_FALSE(m_callback2_ptr.unique());
    m_holder.remove_listener("topic!", m_callback1_ptr);
    m_holder.remove_listener("topic!", m_callback2_ptr);
    EXPECT_TRUE(m_callback1_ptr.unique());
    EXPECT_TRUE(m_callback2_ptr.unique());
}

TEST_F(topic_holder_fixture, send_message) {
    m_holder.add_listener("topic!", m_callback1_ptr);
    m_holder.add_listener("topic!", m_callback2_ptr);
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
    m_holder.add_listener("topic!", m_callback1_ptr);
    m_holder.add_listener("topic!", m_callback2_ptr);
    EXPECT_EQ(m_holder.keys(), std::vector<std::string>{"topic!"});
    m_holder.add_listener("topic", m_callback1_ptr);
    auto vector1 = std::vector<std::string>{"topic", "topic!"};
    EXPECT_EQ(m_holder.keys(), vector1);
    m_holder.remove_listener("topic!", m_callback1_ptr);
    EXPECT_EQ(m_holder.keys(), vector1);
    m_holder.remove_listener("topic!", m_callback2_ptr);
    EXPECT_EQ(m_holder.keys(), std::vector<std::string>{"topic"});

}