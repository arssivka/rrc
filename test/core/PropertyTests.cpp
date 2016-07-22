/**
 *  @autor tekatod
 *  @date 7/21/16
 */

#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "rrc/Property.h"


TEST(set_get_check, test_int_set_get) {
    rrc::Property p;
    p.set(42);
    EXPECT_EQ(42, p.get<int>());
}

TEST(set_get_check, test_int_type) {
    rrc::Property p;
    p.set(42);
    ASSERT_TRUE(typeid(int)== typeid(p.get<int>()));
}

TEST(set_get_check, test_float_set_get) {
    rrc::Property p;
    p.set(42.0);
    EXPECT_EQ(42.0, p.get<float>());
}

TEST(set_get_check, test_float_type) {
    rrc::Property p;
    p.set(42.0);
    ASSERT_TRUE(typeid(float)== typeid(p.get<float>()));
}

TEST(set_get_check, test_bool_set_get) {
    rrc::Property p;
    p.set(true);
    EXPECT_EQ(true, p.get<bool>());
}

TEST(set_get_check, test_bool_type) {
    rrc::Property p;
    p.set(true);
    ASSERT_TRUE(typeid(bool)== typeid(p.get<bool>()));
}

TEST(set_get_check, test_string_set_get) {
    rrc::Property p;
    p.set("SorokDva");
    EXPECT_EQ("SorokDva", p.get<std::string>());
}

TEST(set_get_check, test_int_type) {
    rrc::Property p;
    p.set("SorokDva");
    ASSERT_TRUE(typeid(std::string)== typeid(p.get<std::string>()));
}

TEST(set_get_check, non_template_getter_int) {
    rrc::Property p;
    p.set(42);
    EXPECT_EQ(42, p.getInt());
}

TEST(set_get_check, non_template_getter_float) {
    rrc::Property p;
    p.set(42.0);
    EXPECT_EQ(42.0, p.getFloat());
}

TEST(set_get_check, non_template_getter_bool) {
    rrc::Property p;
    p.set(true);
    EXPECT_EQ(true, p.getBool());
}

TEST(set_get_check, non_template_getter_string) {
    rrc::Property p;
    p.set("SorokDva");
    EXPECT_EQ("SorokDva", p.getString());
}