/**
 *  @autor tekatod
 *  @date 7/22/16
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/Settings.h"
#include "rrc/Property.h"

using namespace rrc;

TEST(SettingsTest, AddTest) {
    Settings sts;
    Property prp;
    prp.set("testprp");
    sts.set("test_key", prp);
    EXPECT_EQ(true, sts.contains("test_key"));
}

TEST(SettingsTest, AddGetTest) {
    Settings sts;
    Property prp;
    prp.set("testprp");
    sts.set("test_key", prp);
    Property prp1;
    prp1 = sts.get("test_key");
    EXPECT_EQ(prp.getString(), prp1.getString());
}

TEST(SettingsTest, UpdateTest) {
    Settings sts;
    Property prp;
    prp.set("testprp");
    sts.set("test_key", prp);
    sts.set("test_key", "test2");
    EXPECT_EQ("test2", sts.get("test_key").getString());
}

TEST(SettingsTest, UpdateNewPropertyTest) {
    Settings sts;
    Property prp;
    prp.set("testprp");
    Property prp1;
    prp1.set("42");
    sts.set("test_key", prp);
    sts.set("test_key", prp1);
    EXPECT_EQ("42", sts.get("test_key").getString());
}

TEST(SettingsTest, RemoveTest) {
    Settings sts;
    Property prp;
    prp.set("testprp");
    sts.set("test_key", prp);
    sts.remove("test_key");
    EXPECT_FALSE(sts.contains("test_key"));
}