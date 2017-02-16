/**
 *  @autor tekatod
 *  @date 7/21/16
 */

#include <gtest/gtest.h>
#include <rrc/core/Table.h>
#include <rrc/core/Array.h>

using namespace rrc;

TEST(PropertyTests, TypeGetterTests) {
    EXPECT_EQ(Property::getType<String>(), PropertyType::String);
    EXPECT_EQ(Property::getType<Number>(), PropertyType::Number);
    EXPECT_EQ(Property::getType<Boolean>(), PropertyType::Boolean);
    EXPECT_EQ(Property::getType<Array>(), PropertyType::Array);
    EXPECT_EQ(Property::getType<Table>(), PropertyType::Table);
    EXPECT_EQ(Property::getType<Nil>(), PropertyType::Nil);
}

TEST(PropertyTests, NilTests) {
    Property property;
    EXPECT_TRUE(property.isNil());
    EXPECT_TRUE(property.isValid());
    EXPECT_FALSE(property.isArray());
    EXPECT_FALSE(property.isBoolean());
    EXPECT_FALSE(property.isNumber());
    EXPECT_FALSE(property.isTable());
    EXPECT_FALSE(property.isString());
    Number number;
    Boolean boolean;
    String string;
    Array array;
    Table table;
    EXPECT_FALSE(property.tryGetNumber(number));
    EXPECT_FALSE(property.tryGetBoolean(boolean));
    EXPECT_FALSE(property.tryGetString(string));
    EXPECT_FALSE(property.tryGetArray(array));
    EXPECT_FALSE(property.tryGetTable(table));
    EXPECT_EQ(property.getType(), PropertyType::Nil);
}

TEST(PropertyTests, StringTests) {
    String string("42");
    Property property(string);
    EXPECT_EQ(property.getType(), PropertyType::String);
    EXPECT_TRUE(property.isValid());
    EXPECT_TRUE(property.isString());
    EXPECT_FALSE(property.isArray());
    EXPECT_FALSE(property.isBoolean());
    EXPECT_FALSE(property.isNumber());
    EXPECT_FALSE(property.isTable());
    EXPECT_FALSE(property.isNil());
    String string1;
    EXPECT_TRUE(property.tryGetString(string1));
    EXPECT_EQ(string1, string);
    Property property1(String("42"));
    String string2;
    EXPECT_TRUE(property1.tryGetString(string2));
    EXPECT_EQ(string2, string);
    EXPECT_TRUE(property == property1);
    EXPECT_FALSE(property != property1);
    Property property2(String("abc"));
    std::string stdString1("42");
    std::string stdString2("abc");
    EXPECT_EQ(property < property2, stdString1 < stdString2);
    EXPECT_EQ(property > property2, stdString1 > stdString2);
    EXPECT_EQ(property >= property2, stdString1 >= stdString2);
    EXPECT_EQ(property <= property2, stdString1 <= stdString2);
}

TEST(PropertyTests, NumberTests) {
    Number number(42.0);
    Property property(number);
    EXPECT_EQ(property.getType(), PropertyType::Number);
    EXPECT_TRUE(property.isValid());
    EXPECT_FALSE(property.isString());
    EXPECT_FALSE(property.isArray());
    EXPECT_FALSE(property.isBoolean());
    EXPECT_TRUE(property.isNumber());
    EXPECT_FALSE(property.isTable());
    EXPECT_FALSE(property.isNil());
    Number number1;
    EXPECT_TRUE(property.tryGetNumber(number1));
    EXPECT_EQ(number1, number);
    Property property1(Number(42.0));
    Number number2;
    EXPECT_TRUE(property1.tryGetNumber(number2));
    EXPECT_EQ(number2, number);
    EXPECT_TRUE(property == property1);
    EXPECT_FALSE(property != property1);
    Property property2(Number(24.0));
    double stdDouble = 42.0;
    double stdDouble1 = 24.0;
    EXPECT_EQ(property < property2, stdDouble < stdDouble1);
    EXPECT_EQ(property > property2, stdDouble > stdDouble1);
    EXPECT_EQ(property >= property2, stdDouble >= stdDouble1);
    EXPECT_EQ(property <= property2, stdDouble <= stdDouble1);
}

TEST(PropertyTests, BooleanTests) {
    Boolean boolean(true);
    Property property(boolean);
    EXPECT_EQ(property.getType(), PropertyType::Boolean);
    EXPECT_TRUE(property.isValid());
    EXPECT_FALSE(property.isString());
    EXPECT_FALSE(property.isArray());
    EXPECT_TRUE(property.isBoolean());
    EXPECT_FALSE(property.isNumber());
    EXPECT_FALSE(property.isTable());
    EXPECT_FALSE(property.isNil());
    Boolean boolean1;
    EXPECT_TRUE(property.tryGetBoolean(boolean1));
    EXPECT_EQ(boolean1, boolean);
    Property property1(Boolean(true));
    Boolean boolean2;
    EXPECT_TRUE(property1.tryGetBoolean(boolean2));
    EXPECT_EQ(boolean2, boolean);
    EXPECT_TRUE(property == property1);
    EXPECT_FALSE(property != property1);
    Property property2(Boolean(false));
    bool stdBool = true;
    bool stdBool1 = false;
    EXPECT_EQ(property < property2, stdBool < stdBool1);
    EXPECT_EQ(property > property2, stdBool > stdBool1);
    EXPECT_EQ(property >= property2, stdBool >= stdBool1);
    EXPECT_EQ(property <= property2, stdBool <= stdBool1);
}

TEST(PropertyTest, SettersTests) {
    Property property;
    EXPECT_TRUE(property.isNil());
    EXPECT_TRUE(property.isValid());
    EXPECT_FALSE(property.isArray());
    EXPECT_FALSE(property.isBoolean());
    EXPECT_FALSE(property.isNumber());
    EXPECT_FALSE(property.isTable());
    EXPECT_FALSE(property.isString());
    Boolean boolean(true);
    property.setBoolean(boolean);
    EXPECT_EQ(property.getType(), PropertyType::Boolean);
    EXPECT_TRUE(property.isValid());
    EXPECT_FALSE(property.isString());
    EXPECT_FALSE(property.isArray());
    EXPECT_TRUE(property.isBoolean());
    EXPECT_FALSE(property.isNumber());
    EXPECT_FALSE(property.isTable());
    EXPECT_FALSE(property.isNil());
    Boolean boolean1;
    EXPECT_TRUE(property.tryGetBoolean(boolean1));
    EXPECT_EQ(boolean1, boolean);
    Number number(42.0);
    property.setNumber(number);
    EXPECT_EQ(property.getType(), PropertyType::Number);
    EXPECT_TRUE(property.isValid());
    EXPECT_FALSE(property.isString());
    EXPECT_FALSE(property.isArray());
    EXPECT_FALSE(property.isBoolean());
    EXPECT_TRUE(property.isNumber());
    EXPECT_FALSE(property.isTable());
    EXPECT_FALSE(property.isNil());
    Number number1;
    EXPECT_TRUE(property.tryGetNumber(number1));
    EXPECT_EQ(number1, number);
    Property property1(Number(42.0));
    Number number2;
    EXPECT_TRUE(property1.tryGetNumber(number2));
    EXPECT_EQ(number2, number);
    String string("42");
    property.setString(string);
    EXPECT_EQ(property.getType(), PropertyType::String);
    EXPECT_TRUE(property.isValid());
    EXPECT_TRUE(property.isString());
    EXPECT_FALSE(property.isArray());
    EXPECT_FALSE(property.isBoolean());
    EXPECT_FALSE(property.isNumber());
    EXPECT_FALSE(property.isTable());
    EXPECT_FALSE(property.isNil());
    String string1;
    EXPECT_TRUE(property.tryGetString(string1));
    EXPECT_EQ(string1, string);
    property.setNil();
    EXPECT_TRUE(property.isNil());
    EXPECT_TRUE(property.isValid());
    EXPECT_FALSE(property.isArray());
    EXPECT_FALSE(property.isBoolean());
    EXPECT_FALSE(property.isNumber());
    EXPECT_FALSE(property.isTable());
    EXPECT_FALSE(property.isString());
}

TEST(PropertyTests, RValueSettersTests) {
    Property property;
    String string("42");
    String string1;
    property.setString(string);
    EXPECT_TRUE(property.tryGetString(string1));
    EXPECT_EQ(string, string1);
    Number number;
    Number number1(42.0);
    property.setNumber(Number(42.0));
    EXPECT_TRUE(property.tryGetNumber(number));
    EXPECT_EQ(number, number1);
    Boolean boolean(true);
    Boolean boolean1;
    property.setBoolean(Boolean(true));
    EXPECT_TRUE(property.tryGetBoolean(boolean1));
    EXPECT_EQ(boolean, boolean1);
}
// /TODO:: tests of array and table.