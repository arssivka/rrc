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
    std::vector<std::shared_ptr<abstract_queue_adapter<int>>> vector;
    vector.push_back(factory.create_shared_pointer());
    vector.push_back(factory.create_shared_pointer());
    EXPECT_EQ(vector.size(), (size_t) 2);
}

TEST(queue_adapter_factory_tests, unique_ptr_test) {
    queue_adapter_factory<int> factory = queue_adapter_factory<int>::create<rrc::stl_queue_adapter<int>>();
    std::vector<std::unique_ptr<abstract_queue_adapter<int>>> vector;
    vector.push_back(factory.create_unique_pointer());
    vector.push_back(factory.create_unique_pointer());
    EXPECT_EQ(vector.size(), (size_t) 2);
}

TEST(queue_adapter_factory_tests, assigment_operators) {
    queue_adapter_factory<int> factory = queue_adapter_factory<int>::create<rrc::stl_queue_adapter<int>>();
    queue_adapter_factory<int> factory1 = factory;
    std::vector<std::shared_ptr<abstract_queue_adapter<int>>> vector;
    vector.push_back(factory1.create_shared_pointer());
    vector.push_back(factory1.create_shared_pointer());
    EXPECT_EQ(vector.size(), (size_t) 2);

}