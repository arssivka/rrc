/**
 *  @autor tekatod
 *  @date 1/23/17
 */
#include "gtest/gtest.h"
#include <rrc/meta.h>
#include "rrc/core/StructureTypeQuantityGenerator.h"
#include <map>

using namespace rrc;

TEST(TypeQuantityTests, NotNestedTests) {
    typedef StructureTypeQuantitySequence<MetaList<int>> generator;
    bool same = std::is_same<generator, MetaIntegralSequence<size_t>>::value;
    EXPECT_TRUE(same);
    typedef StructureTypeQuantitySequence<MetaList<std::vector<int>>> generator1;
    bool same1 = std::is_same<generator1, MetaIntegralSequence<size_t>>::value;
    EXPECT_TRUE(same1);
    typedef StructureTypeQuantitySequence<MetaList<std::map<int, int>>> generator2;
    bool same2 = std::is_same<generator2, MetaIntegralSequence<size_t, 2>>::value;
    EXPECT_TRUE(same2);
    typedef StructureTypeQuantitySequence<MetaList<std::tuple<int, int, int>>> generator3;
    bool same3 = std::is_same<generator3, MetaIntegralSequence<size_t, 3>>::value;
    EXPECT_TRUE(same3);
    typedef StructureTypeQuantitySequence<MetaList<std::pair<int, int>>> generator4;
    bool same4 = std::is_same<generator4, MetaIntegralSequence<size_t, 2>>::value;
    EXPECT_TRUE(same4);
}

TEST(TypeQuantityTests, NestedTests) {
    typedef StructureTypeQuantitySequence<MetaList<std::vector<std::vector<int>>>> generator;
    bool same = std::is_same<generator, MetaIntegralSequence<size_t>>::value;
    EXPECT_TRUE(same);
    typedef StructureTypeQuantitySequence<MetaList<std::map<int, std::vector<int>>>> generator1;
    bool same1 = std::is_same<generator1, MetaIntegralSequence<size_t, 2>>::value;
    EXPECT_TRUE(same1);
    typedef StructureTypeQuantitySequence<MetaList<std::vector<std::map<int, std::vector<int>>>>> generator2;
    bool same2 = std::is_same<generator2, MetaIntegralSequence<size_t, 2>>::value;
    EXPECT_TRUE(same2);
    typedef StructureTypeQuantitySequence<MetaList<std::pair<std::map<int, int>, std::map<int, int>>>> generator3;
    bool same3 = std::is_same<generator3, MetaIntegralSequence<size_t, 2, 2, 2>>::value;
    EXPECT_TRUE(same3);
}