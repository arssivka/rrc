/**
 *  @autor tekatod
 *  @date 2/2/17
 */

#include <iostream>
#include <gtest/gtest.h>
#include <rrc/core.h>

using namespace rrc;

TEST(queue_adapter_factory_tests, shared_ptr_test) {
    queue_adapter_factory<int> factory = queue_adapter_factory<int>::create<rrc::stl_queue_adapter<int>>();
    std::vector<std::shared_ptr<abstract_queue_adapter<int>>> test_vector;
    test_vector.push_back(factory.create_shared_pointer());
    test_vector.push_back(factory.create_shared_pointer());
    EXPECT_EQ(test_vector.size(), (size_t) 2);
}

TEST(queue_adapter_factory_tests, unique_ptr_test) {
    queue_adapter_factory<int> factory = queue_adapter_factory<int>::create<rrc::stl_queue_adapter<int>>();
    std::vector<std::unique_ptr<abstract_queue_adapter<int>>> test_vector;
    test_vector.push_back(factory.create_unique_pointer());
    test_vector.push_back(factory.create_unique_pointer());
    EXPECT_EQ(test_vector.size(), (size_t) 2);
}