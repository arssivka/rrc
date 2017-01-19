/**
 *  @autor tekatod
 *  @date 1/11/17
 */
#include "gtest/gtest.h"
#include <rrc/core/MetaFunctions.h>
#include <rrc/core/MetaGenerators.h>
#include <rrc/core/MetaArray.h>
#include <rrc/core/Message.h>

using namespace rrc::meta;
using namespace rrc;

// We can't test fucking metaprogramming without fucking types!
typedef int fuck;


TEST(MetaTest, Message) {
    Message fuckMessage(0, 0, 0, 0, 0);
    auto res = fuckMessage.getMetaData();
    auto pack = meta::Pack<int8_t, INT32_ID, INT32_ID>::value;
    EXPECT_EQ(res[0], pack);
    EXPECT_EQ(res.getSize(), (size_t) 3);
    Message notOnlyFuckMessage(std::vector<fuck>{0, 0, 0}, 0);
    auto res1 = notOnlyFuckMessage.getMetaData();
    auto pack1 = meta::Pack<int8_t, INT32_ARRAY_ID, INT32_ID>::value;
    EXPECT_EQ(res1[0], pack1);
    EXPECT_EQ(res1.getSize(), (size_t) 1);
    Message notOnlyFuckMessage1(std::map<fuck, fuck>{});
    auto res2 = notOnlyFuckMessage1.getMetaData();
    auto pack2 = meta::Pack<int8_t, STRUCTURE_ARRAY_ID, INT32_ID>::value;
    EXPECT_EQ(res2[0], pack2);
    EXPECT_EQ(res2.getSize(), (size_t) 2);
    Message veryFuckMessage((double) 0.0, (float) 0.0, (bool) (false));
    auto res3 = veryFuckMessage.getMetaData();
    auto pack3 = meta::Pack<int8_t, DOUBLE_ID, FLOAT_ID>::value;
    EXPECT_EQ(res3.getSize(), (size_t) 2);
    EXPECT_EQ(res3[0], pack3);
    EXPECT_EQ(res3[1], INT8_ID);
}