/**
 *  @autor tekatod
 *  @date 1/23/17
 */
#include "gtest/gtest.h"
#include <rrc/meta.h>
#include "rrc/core/StructureTypeQuantityGenerator.h"
#include <map>

using namespace rrc::meta;
using namespace rrc;

TEST(TypeQuantityTests, NotNestedTests) {
    typedef StructureTypeQuantityGenerator<List<int>> generator;
    bool same = std::is_same<generator, IntegralSequence<size_t>>::value;
    EXPECT_TRUE(same);
    typedef StructureTypeQuantityGenerator<List<std::vector<int>>> generator1;
    bool same1 = std::is_same<generator1, IntegralSequence<size_t>>::value;
    EXPECT_TRUE(same1);
    typedef StructureTypeQuantityGenerator<List<std::map<int, int>>> generator2;
    bool same2 = std::is_same<generator2, IntegralSequence<size_t, 2>>::value;
    EXPECT_TRUE(same2);
    typedef StructureTypeQuantityGenerator<List<std::tuple<int, int, int>>> generator3;
    bool same3 = std::is_same<generator3, IntegralSequence<size_t, 3>>::value;
    EXPECT_TRUE(same3);
    typedef StructureTypeQuantityGenerator<List<std::pair<int, int>>> generator4;
    bool same4 = std::is_same<generator4, IntegralSequence<size_t, 2>>::value;
    EXPECT_TRUE(same4);
}

TEST(TypeQuantityTests, NestedTests) {
    typedef StructureTypeQuantityGenerator<List<std::vector<std::vector<int>>>> generator;
    bool same = std::is_same<generator, IntegralSequence<size_t>>::value;
    EXPECT_TRUE(same);
    typedef StructureTypeQuantityGenerator<List<std::map<int, std::vector<int>>>> generator1;
    bool same1 = std::is_same<generator1, IntegralSequence<size_t, 2>>::value;
    EXPECT_TRUE(same1);
    typedef StructureTypeQuantityGenerator<List<std::vector<std::map<int, std::vector<int>>>>> generator2;
    bool same2 = std::is_same<generator2, IntegralSequence<size_t, 2>>::value;
    EXPECT_TRUE(same2);
    typedef StructureTypeQuantityGenerator<List<std::pair<std::map<int, int>, std::map<int, int>>>> generator3;
    bool same3 = std::is_same<generator3, IntegralSequence<size_t, 2, 2, 2>>::value;
    EXPECT_TRUE(same3);
}