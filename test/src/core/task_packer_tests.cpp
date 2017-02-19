/**
 *  @autor tekatod
 *  @date 2/13/17
 */

#include <gtest/gtest.h>
#include <rrc/core/exec.h>
#include <rrc/core/stl_queue_adapter.h>
#include <rrc/core/task_packer.h>

using namespace rrc;

TEST(task_packer_tests, basic_non_const_constructor) {
    std::shared_ptr<abstract_queue_adapter<task>> test_adapter_ptr(
            (abstract_queue_adapter<task>*) new stl_queue_adapter<task>());
    task_packer<cow_string> task_packer(test_adapter_ptr, [](cow_string message){
        message->empty();
    });
    cow_string str = make_cow<std::string>("meow!");
    task_packer.enqueue_task(str);
    EXPECT_FALSE(task_packer.is_orphan());
    EXPECT_TRUE(exec_once(test_adapter_ptr));
}

TEST(task_packer_tests, basic_orphan) {
    std::shared_ptr<abstract_queue_adapter<task>> test_adapter_ptr(
            (abstract_queue_adapter<task>*) new stl_queue_adapter<task>());
    task_packer<cow_string> task_packer(test_adapter_ptr, [](cow_string message){
        message->empty();
    });
    EXPECT_FALSE(task_packer.is_orphan());
    test_adapter_ptr = nullptr;
    EXPECT_TRUE(task_packer.is_orphan());
}