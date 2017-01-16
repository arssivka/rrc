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
    EXPECT_EQ(res[0], INT32_ID);
    EXPECT_EQ(fuckMessage.getMetaDataSize(), (int_fast8_t) 1);
    Message notOnlyFuckMessage(std::vector<fuck>{0, 0, 0}, 0);
    auto res1 = notOnlyFuckMessage.getMetaData();
    auto pack = meta::Pack<int8_t, INT32_ID, INT32_ID>::value;
    EXPECT_EQ((int_fast8_t) 1, notOnlyFuckMessage.getMetaDataSize());
    EXPECT_EQ(res1[0], pack);
}