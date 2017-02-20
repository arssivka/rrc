/**
 *  @autor tekatod
 *  @date 2/7/17
 */

#include <gtest/gtest.h>
#include <rrc/core.h>

using namespace rrc;


class flag_setter {
public:
    flag_setter(bool& _flag)
            : m_flag(_flag) {
        m_flag = false;
    }

    void operator()() {
        m_flag = true;
    }

private:
    bool& m_flag;
};


class exec_fixture
        : public ::testing::Test {
protected:

    void SetUp() override {
        m_task_queue.reset(new stl_queue_adapter<task>());
        m_task_queue->enqueue(flag_setter(m_first_flag));
        m_task_queue->enqueue(flag_setter(m_second_flag));
        m_task_queue->enqueue(flag_setter(m_third_flag));
    }

protected:
    bool m_first_flag;
    bool m_second_flag;
    bool m_third_flag;
    std::shared_ptr<abstract_queue_adapter<task>> m_task_queue;

};

TEST_F(exec_fixture, exec_once_1) {
    EXPECT_FALSE(m_first_flag);
    EXPECT_FALSE(m_second_flag);
    EXPECT_FALSE(m_third_flag);
    exec_once(m_task_queue);
    EXPECT_TRUE(m_first_flag);
    EXPECT_FALSE(m_second_flag);
    EXPECT_FALSE(m_third_flag);
}

TEST_F(exec_fixture, exec_once_2) {
    EXPECT_FALSE(m_first_flag);
    EXPECT_FALSE(m_second_flag);
    EXPECT_FALSE(m_third_flag);
    exec_once(m_task_queue);
    exec_once(m_task_queue);
    EXPECT_TRUE(m_first_flag);
    EXPECT_TRUE(m_second_flag);
    EXPECT_FALSE(m_third_flag);
}

TEST_F(exec_fixture, exec_once_3) {
    EXPECT_FALSE(m_first_flag);
    EXPECT_FALSE(m_second_flag);
    EXPECT_FALSE(m_third_flag);
    exec_once(m_task_queue);
    exec_once(m_task_queue);
    exec_once(m_task_queue);
    EXPECT_TRUE(m_first_flag);
    EXPECT_TRUE(m_second_flag);
    EXPECT_TRUE(m_third_flag);
}

TEST_F(exec_fixture, exec_all) {
    EXPECT_FALSE(m_first_flag);
    EXPECT_FALSE(m_second_flag);
    EXPECT_FALSE(m_third_flag);
    exec_all(m_task_queue);
    EXPECT_TRUE(m_first_flag);
    EXPECT_TRUE(m_second_flag);
    EXPECT_TRUE(m_third_flag);
}