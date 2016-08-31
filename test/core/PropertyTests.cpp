/**
 *  @autor tekatod
 *  @date 7/21/16
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/Property.h"


TEST(PropertyTest, IntSetGetTest) {
    rrc::Property p;
    p.set(42);
    EXPECT_EQ(42, p.get<int>());
}

TEST(PropertyTest, IntTypeTest) {
    rrc::Property p;
    p.set(42);
    ASSERT_TRUE(typeid(int) == typeid(p.get<int>()));
}

TEST(PropertyTest, FloatSetGetTest) {
    rrc::Property p;
    p.set((float)42.0);
    EXPECT_EQ(42.0, p.get<float>());
}

TEST(PropertyTest, FloatTypeTest) {
    rrc::Property p;
    p.set((float)42.0);
    ASSERT_TRUE(typeid(float)== typeid(p.get<float>()));
}

TEST(PropertyTest, BoolSetGetTest) {
    rrc::Property p;
    p.set(true);
    EXPECT_EQ(true, p.get<bool>());
}

TEST(PropertyTest, BoolTypeTest) {
    rrc::Property p;
    p.set(true);
    ASSERT_TRUE(typeid(bool) == typeid(p.get<bool>()));
}

TEST(PropertyTest, StringSetGetTest) {
    rrc::Property p;
    p.set("SorokDva");
    EXPECT_EQ("SorokDva", p.get<std::string>());
}

TEST(PropertyTest, StringTypeTest) {
    rrc::Property p;
    p.set("SorokDva");
    ASSERT_TRUE(typeid(std::string) == typeid(p.get<std::string>()));
}

TEST(PropertyTest, NonTemplateGetterIntTest) {
    rrc::Property p;
    p.set(42);
    EXPECT_EQ(42, p.getInt());
}

TEST(PropertyTest, NonTemplateGetterFloatTest) {
    rrc::Property p;
    p.set((float) 42.0);
    EXPECT_EQ(42.0, p.getFloat());
}

TEST(PropertyTest, NonTemplateGetterBoolTest) {
    rrc::Property p;
    p.set(true);
    EXPECT_EQ(true, p.getBool());
}

TEST(PropertyTest, NonTemplateGetterStringTest) {
    rrc::Property p;
    p.set("SorokDva");
    EXPECT_EQ("SorokDva", p.getString());
}

TEST(PropertyTest, BoolToFloatTest) {
    rrc::Property p;
    p.set(true);
    float t = p.get<float>();
    EXPECT_EQ(float(1), t);

}

TEST(PropertyTest, BoolToIntTest) {
    rrc::Property p;
    p.set(true);
    int t = p.get<int>();
    EXPECT_EQ(1, t);
}


TEST(PropertyTest, BoolToStringTest) {
    rrc::Property p;
    p.set(true);
    std::string t = p.get<std::string>();
    EXPECT_EQ("1", t);
}

TEST(PropertyTest, FloatToIntTest) {
    rrc::Property p;
    p.set((float)42.42);
    int t = p.get<int>();
    EXPECT_EQ(42, t);
}

TEST(PropertyTest, FloatToBoolTest) {
    rrc::Property p;
    p.set((float) 42.42);
    bool t = p.get<bool>();
    EXPECT_EQ(true, t);
}

TEST(PropertyTest, FloatToStringTest) {
    rrc::Property p;
    p.set((float)42.42);
    std::string t = p.get<std::string>();
    EXPECT_EQ("42.419998", t); //because of float
}

TEST(PropertyTest, IntToBoolTest) {
    rrc::Property p;
    p.set(42);
    bool t = p.get<bool>();
    EXPECT_EQ(true, t);
}

TEST(PropertyTest, IntToFloatTest) {
    rrc::Property p;
    p.set(42);
    float t = p.get<float>();
    EXPECT_EQ((float)42, t);
}

TEST(PropertyTest, IntToStringTest) {
    rrc::Property p;
    p.set(42);
    std::string t = p.get<std::string>();
    EXPECT_EQ("42", t);
}

TEST(PropertyTest, StringToBoolTest) {
    rrc::Property p;
    p.set("true");
    bool t = p.get<bool>();
    EXPECT_EQ(true, t);
}

TEST(PropertyTest, StringToFloatTest) {
    rrc::Property p;
    p.set("42");
    float t = p.get<float>();
    EXPECT_EQ((float) 42, t);
}

TEST(PropertyTest, StringToIntTest) {
    rrc::Property p;
    p.set("42");
    int t = p.get<int>();
    EXPECT_EQ(42, t);
}