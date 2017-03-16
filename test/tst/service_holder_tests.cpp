/**
 *  @autors tekatod, arssivka
 *  @date 2/13/17
 */

#include <gtest/gtest.h>
#include <rrc/rrc.h>

using namespace rrc;

class service_holder_fixture
        : public ::testing::Test {
protected:
    typedef typename service_holder<std::string, std::string>::callback_type callback_type;
    typedef typename service_holder<std::string, std::string>::listener_type listener_type;

    virtual void SetUp() override {
        m_flage = false;
        m_toli_esho_budet = false;
        m_message = std::string("meow!");
        m_callback = callback_type(
                [this](const std::string& in, std::string& out) -> service_status {
            m_flage = true;
            out = in;
            out[0] = 'M';
            return service_status::ok;
        });
        m_listener = listener_type(
                [this](service_status status, const std::string& msg) {
                    m_toli_esho_budet = service_status::ok == status;
                    m_message = msg;
                    m_message[1] = 'E';
                }
        );
    }

    virtual void TearDown() override {
    }


protected:
    bool m_flage; // it's not a mistake! O_O
    bool m_toli_esho_budet;
    callback_type m_callback;
    listener_type m_listener;
    std::string m_message;
    service_holder<std::string, std::string> m_holder;
};


TEST_F(service_holder_fixture, add_service) {
    EXPECT_TRUE(m_callback.unique());
    m_holder.add_service("fuck", m_callback);
    EXPECT_EQ(m_callback.use_count(), 2);
}

TEST_F(service_holder_fixture, remove_service) {
    EXPECT_TRUE(m_callback.unique());
    m_holder.add_service("fuck", m_callback);
    EXPECT_EQ(m_callback.use_count(), 2);
    m_holder.remove_service(m_callback);
    EXPECT_TRUE(m_callback.unique());
}

TEST_F(service_holder_fixture, call) {
    m_holder.add_service("fuck", m_callback);
    EXPECT_FALSE(m_flage);
    EXPECT_FALSE(m_toli_esho_budet);
    EXPECT_EQ(m_message, "meow!");
    m_holder.call("fuck", m_message, m_listener);
    EXPECT_TRUE(m_flage);
    EXPECT_TRUE(m_toli_esho_budet);
    EXPECT_EQ(m_message, "MEow!");
}

TEST_F(service_holder_fixture, keys) {
    EXPECT_EQ(m_holder.keys(), std::vector<std::string>{});
    m_holder.add_service("fuck", m_callback);
    EXPECT_EQ(m_holder.keys(), std::vector<std::string>{"fuck"});
    m_holder.remove_service(m_callback);
    EXPECT_EQ(m_holder.keys(), std::vector<std::string>{});
}