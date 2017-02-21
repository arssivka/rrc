/**
 *  @autor tekatod
 *  @date 7/22/16
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <rrc/core/stl_queue_adapter.h>
#include "rrc/core/settings_holder.h"

using namespace rrc;

class settings_fixture : public ::testing::Test {
public:
    settings_fixture()
            : m_property1(42.0), m_property2(true) { }

protected:
    settings_holder<std::string> m_settings;
    property m_property1;
    property m_property2;
};

TEST_F(settings_fixture, set_contains_get) {
    m_settings.set_property("ochen_horosho", m_property1);
    m_settings.set_property("ochen_ploho", m_property2);
    property property1;
    property property2;
    EXPECT_TRUE(m_settings.try_get_property("ochen_horosho", property1));
    EXPECT_TRUE(m_settings.try_get_property("ochen_ploho", property2));
    EXPECT_TRUE(m_settings.contains("ochen_horosho"));
    EXPECT_TRUE(m_settings.contains("ochen_ploho"));
    EXPECT_EQ(property1, m_property1);
    EXPECT_EQ(property2, m_property2);
}

TEST_F(settings_fixture, keys_getter) {
    auto keys = m_settings.keys();
    EXPECT_EQ(keys.size(), size_t(0));
    m_settings.set_property("ochen_horosho", m_property1);
    m_settings.set_property("ochen_ploho", m_property2);
    keys = m_settings.keys();
    EXPECT_EQ(keys.size(), size_t(2));
    EXPECT_TRUE(keys[0] == "ochen_horosho" || keys[0] == "ochen_ploho");
    EXPECT_TRUE(keys[1] == "ochen_horosho" || keys[1] == "ochen_ploho");
}

TEST_F(settings_fixture, remove_property) {
    m_settings.set_property("ochen_horosho", m_property1);
    m_settings.set_property("ochen_ploho", m_property2);
    m_settings.remove_property("ochen_ploho");
    property property1;
    EXPECT_FALSE(m_settings.contains("ochen_ploho"));
    EXPECT_FALSE(m_settings.try_get_property("ochen_ploho", property1));
    EXPECT_NE(property1, m_property1);
}

TEST_F(settings_fixture, listeners) {
    property property1;
    property property2;
    property property3("42");
    std::shared_ptr<abstract_queue_adapter<task>> test_adapter_ptr(
            (abstract_queue_adapter<task>*) new stl_queue_adapter<task>());
    std::shared_ptr<task_packer<property>> listener1 =
            std::make_shared<task_packer<property>>(test_adapter_ptr, [&property1](property p){
        property1 = p;
    });
    std::shared_ptr<task_packer<property>> listener2 =
            std::make_shared<task_packer<property>>(test_adapter_ptr, [&property2](property p){
        property2 = p;
    });
    m_settings.add_listener("ochen_horosho", listener1);
    m_settings.add_listener("ochen_ploho", listener2);
    m_settings.set_property("ochen_horosho", m_property1);
    m_settings.set_property("ochen_ploho", m_property2);
    exec_all(test_adapter_ptr);
    EXPECT_EQ(property1, m_property1);
    EXPECT_EQ(property2, m_property2);
    m_settings.remove_listener("ochen_ploho", listener2);
    m_settings.set_property("ochen_ploho", property3);
    exec_all(test_adapter_ptr);
    EXPECT_EQ(property2, m_property2);
    m_settings.remove_property("ochen_horosho");
    exec_all(test_adapter_ptr);
    EXPECT_EQ(property1, property());
}