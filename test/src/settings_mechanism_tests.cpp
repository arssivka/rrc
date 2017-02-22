/**
 *  @autor tekatod
 *  @date 2/21/17
 */
#include <iostream>
#include <gtest/gtest.h>
#include <rrc/core.h>

using namespace rrc;

class settings_mechanism_fixture
        : public ::testing::Test {
protected:

    settings_mechanism_fixture() : m_factory(queue_adapter_factory<task>::create<rrc::stl_queue_adapter<task>>()),
                                   m_task_queue(new stl_queue_adapter<task>()),
                                   m_settings_mechanism(m_task_queue, m_factory),
                                   m_property1(42.0), m_property2(true) { }

protected:
    queue_adapter_factory<task> m_factory;
    std::shared_ptr<abstract_queue_adapter<task>> m_task_queue;
    settings_mechanism m_settings_mechanism;
    property m_property1;
    property m_property2;
};

TEST_F(settings_mechanism_fixture, setter_getter) {
    m_settings_mechanism.set_property("ochen_horosho", m_property1);
    m_settings_mechanism.set_property("ochen_ploho", m_property2);
    property property1;
    property property2;
    exec_all(m_task_queue);
    EXPECT_TRUE(m_settings_mechanism.try_get_property("ochen_horosho", property1));
    EXPECT_TRUE(m_settings_mechanism.try_get_property("ochen_ploho", property2));
    EXPECT_EQ(property1, m_property1);
    EXPECT_EQ(property2, m_property2);
}