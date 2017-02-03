/**
 *  @autor tekatod
 *  @date 2/2/17
 */

#include <iostream>
#include <gtest/gtest.h>
#include <include/QueueAdapter.h>
#include "rrc/core/QueueAdapterFactory.h"

using namespace rrc;

TEST(QueueAdapterFactoryTests, SharedPtrTest) {
    QueueAdapterFactory<int> factory = QueueAdapterFactory<int>::create<QueueAdapter<int>>();
    std::vector<std::shared_ptr<AbstractQueueAdapter<int>>> testVector;
    testVector.push_back(factory.createSharedPointer());
    testVector.push_back(factory.createSharedPointer());
    EXPECT_EQ(testVector.size(), (size_t)2);
}

TEST(QueueAdapterFactoryTests, UniquePtrTest) {
    QueueAdapterFactory<int> factory = QueueAdapterFactory<int>::create<QueueAdapter<int>>();
    std::vector<std::unique_ptr<AbstractQueueAdapter<int>>> testVector;
    testVector.push_back(factory.createUniquePointer());
    testVector.push_back(factory.createUniquePointer());
    EXPECT_EQ(testVector.size(), (size_t)2);
}