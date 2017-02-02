/**
 *  @autor tekatod
 *  @date 1/25/17
 */

#include "gtest/gtest.h"
#include <rrc/core/TypesIdentifiersArray.h>
#include "gmock/gmock.h"
#include <iostream>

using namespace rrc;

TEST(TypesIdentifiersArrayTests, CreateTest) {
    TypesIdentifiersArray typesIdentifiersArray{(int) 0, (int) 0, (int) 0};
    for (auto  x : typesIdentifiersArray) {
        std::cout << (int) x << std::endl;
    }
}