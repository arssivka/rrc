/**
 *  @autor tekatod
 *  @date 7/21/16
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/core/Property.h"

using namespace rrc;

TEST(PropertyTest, IntSetGetTest) {
    Property p;
    p.set(42);
    EXPECT_EQ(42, p.get<int>());
}

TEST(PropertyTest, IntTypeTest) {
    Property p;
    p.set(42);
    ASSERT_TRUE(typeid(int) == typeid(p.get<int>()));
}

TEST(PropertyTest, FloatSetGetTest) {
    Property p;
    p.set((float)42.0);
    EXPECT_EQ(42.0, p.get<float>());
}

TEST(PropertyTest, FloatTypeTest) {
    Property p;
    p.set((float)42.0);
    ASSERT_TRUE(typeid(float)== typeid(p.get<float>()));
}

TEST(PropertyTest, BoolSetGetTest) {
    Property p;
    p.set(true);
    EXPECT_EQ(true, p.get<bool>());
}

TEST(PropertyTest, BoolTypeTest) {
    Property p;
    p.set(true);
    ASSERT_TRUE(typeid(bool) == typeid(p.get<bool>()));
}

TEST(PropertyTest, StringSetGetTest) {
    Property p;
    p.set("SorokDva");
    EXPECT_EQ("SorokDva", p.get<std::string>());
}

TEST(PropertyTest, StringTypeTest) {
    Property p;
    p.set("SorokDva");
    ASSERT_TRUE(typeid(std::string) == typeid(p.get<std::string>()));
}

TEST(PropertyTest, NonTemplateGetterIntTest) {
    Property p;
    p.set(42);
    EXPECT_EQ(42, p.getInt());
}

TEST(PropertyTest, NonTemplateGetterFloatTest) {
    Property p;
    p.set((float) 42.0);
    EXPECT_EQ(42.0, p.getFloat());
}

TEST(PropertyTest, NonTemplateGetterBoolTest) {
    Property p;
    p.set(true);
    EXPECT_EQ(true, p.getBool());
}

TEST(PropertyTest, NonTemplateGetterStringTest) {
    Property p;
    p.set("SorokDva");
    EXPECT_EQ("SorokDva", p.getString());
}

TEST(PropertyTest, BoolToFloatTest) {
    Property p;
    p.set(true);
    float t = p.get<float>();
    EXPECT_EQ(float(1), t);

}

TEST(PropertyTest, BoolToIntTest) {
    Property p;
    p.set(true);
    int t = p.get<int>();
    EXPECT_EQ(1, t);
}


TEST(PropertyTest, BoolToStringTest) {
    Property p;
    p.set(true);
    std::string t = p.get<std::string>();
    EXPECT_EQ("1", t);
}

TEST(PropertyTest, FloatToIntTest) {
    Property p;
    p.set((float)42.42);
    int t = p.get<int>();
    EXPECT_EQ(42, t);
}

TEST(PropertyTest, FloatToBoolTest) {
    Property p;
    p.set((float) 42.42);
    bool t = p.get<bool>();
    EXPECT_EQ(true, t);
}

TEST(PropertyTest, FloatToStringTest) {
    Property p;
    p.set((float)42.42);
    std::string t = p.get<std::string>();
    EXPECT_EQ("42.419998", t); //because of float
}

TEST(PropertyTest, IntToBoolTest) {
    Property p;
    p.set(42);
    bool t = p.get<bool>();
    EXPECT_EQ(true, t);
}

TEST(PropertyTest, IntToFloatTest) {
    Property p;
    p.set(42);
    float t = p.get<float>();
    EXPECT_EQ((float)42, t);
}

TEST(PropertyTest, IntToStringTest) {
    Property p;
    p.set(42);
    std::string t = p.get<std::string>();
    EXPECT_EQ("42", t);
}

TEST(PropertyTest, StringToBoolTest) {
    Property p;
    p.set("true");
    bool t = p.get<bool>();
    EXPECT_EQ(true, t);
}

TEST(PropertyTest, StringToFloatTest) {
    Property p;
    p.set("42");
    float t = p.get<float>();
    EXPECT_EQ((float) 42, t);
}

TEST(PropertyTest, StringToIntTest) {
    Property p;
    p.set("42");
    int t = p.get<int>();
    EXPECT_EQ(42, t);
}