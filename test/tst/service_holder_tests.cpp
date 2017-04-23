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

    virtual void SetUp() override {
        m_flage = false;
        m_toli_esho_budet = false;
        m_message = string("meow!");
        m_callback = service_callback(
                [this](const string& in, string& out) -> result_code {
            m_flage = true;
            out = rrc::string("Meow");
            return RESULT_CODE_SUCCESS;
        });
        m_listener = service_result_callback(
                [this](result_code stat, const string& msg) {
                    m_toli_esho_budet = (RESULT_CODE_SUCCESS == stat);
                    m_message = rrc::string("MEow");
                }
        );
    }

    virtual void TearDown() override {
    }


protected:
    bool m_flage; // it's not a mistake! O_O
    bool m_toli_esho_budet;
    service_callback m_callback;
    service_result_callback m_listener;
    string m_message;
    service_holder m_holder;
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
    EXPECT_EQ(m_message, "MEow");
}