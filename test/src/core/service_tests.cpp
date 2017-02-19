/**
 *  @autors tekatod, arssivka
 *  @date 2/13/17
 */

#include <gtest/gtest.h>
#include <rrc/core/abstract_task_queue_adapter.h>
#include <rrc/core/stl_queue_adapter.h>
#include <rrc/core/service.h>

using namespace rrc;

class service_fixture
        : public ::testing::Test {
protected:
    virtual void SetUp() override {
        m_message = make_cow<std::string>("meow!");
        m_test_queue.reset((abstract_task_queue_adapter*) new stl_queue_adapter<task>());
        m_result_queue.reset((abstract_task_queue_adapter*) new stl_queue_adapter<task>());
    }

    virtual void TearDown() override {
    }


protected:
    cow_string m_message;
    std::shared_ptr<abstract_task_queue_adapter> m_test_queue;
    std::shared_ptr<abstract_task_queue_adapter> m_result_queue;
};

TEST_F(service_fixture, call_test) {
    cow_string result;
    std::shared_ptr<task_packer<cow_string>> callback = std::make_shared<task_packer<cow_string>>(
            m_result_queue, [&result](cow_string buffer) {
                result = std::move(buffer);
            });
    service service(m_test_queue, [](cow_string b) -> cow_string {
        return b;
    });
    EXPECT_TRUE(service.call(callback, m_message));
    EXPECT_TRUE(m_test_queue->exec_once());
    EXPECT_TRUE(m_result_queue->exec_once());
    EXPECT_EQ(*m_message, *result);
}