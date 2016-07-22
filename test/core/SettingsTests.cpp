/**
 *  @autor tekatod
 *  @date 7/22/16
 */

#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "rrc/Settings.h"
#include "rrc/Property.h"

TEST(add_or_update_test, add_test) {
    rrc::Settings sts;
    rrc::Property prp;
    prp.set("testprp");
    sts.addOrUpdate("test_key", prp);
    EXPECT_EQ(true, sts.contains("test_key"));
}