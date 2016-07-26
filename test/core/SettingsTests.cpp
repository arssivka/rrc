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
    sts.set("test_key", prp);
    EXPECT_EQ(true, sts.contains("test_key"));
}

TEST(add_or_update_test, add_get_test) {
    rrc::Settings sts;
    rrc::Property prp;
    prp.set("testprp");
    sts.set("test_key", prp);
    rrc::Property prp1;
    prp1 = sts.get("test_key");
    EXPECT_EQ(prp.getString(), prp1.getString());
}

TEST(add_or_update_test, update_test) {
    rrc::Settings sts;
    rrc::Property prp;
    prp.set("testprp");
    sts.set("test_key", prp);
    sts.set("test_key", "test2");
    EXPECT_EQ("test2", sts.get("test_key").getString());
}

TEST(add_or_update_test, update_new_property_test) {
    rrc::Settings sts;
    rrc::Property prp;
    prp.set("testprp");
    rrc::Property prp1;
    prp.set("42");
    sts.set("test_key", prp);
    sts.set("test_key", prp1);
    EXPECT_EQ("42", sts.get("test_key").getString());
}

TEST(remove_test, rem_test) {
    rrc::Settings sts;
    rrc::Property prp;
    prp.set("testprp");
    sts.set("test_key", prp);
    sts.remove("test_key");
    EXPECT_FALSE(sts.contains("test_key"));
}