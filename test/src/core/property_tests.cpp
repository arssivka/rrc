/**
 *  @autor tekatod
 *  @date 7/21/16
 */

#include <gtest/gtest.h>
#include <rrc/core/property.h>

using namespace rrc;


TEST(property_tests, string_test) {
    std::string string("42");
    property property1(string);
    EXPECT_EQ(property1.type(), property_type::STRING);
    EXPECT_TRUE(property1.is_valid());
    EXPECT_TRUE(property1.is_string());
    EXPECT_FALSE(property1.is_vector());
    EXPECT_FALSE(property1.is_bool());
    EXPECT_FALSE(property1.is_double());
    EXPECT_FALSE(property1.is_map());
    std::string string1;
    EXPECT_TRUE(property1.try_get_string(string1));
    EXPECT_EQ(string1, string);
    property property2(std::string("42"));
    std::string string2;
    EXPECT_TRUE(property2.try_get_string(string2));
    EXPECT_EQ(string2, string);
    EXPECT_TRUE(property1 == property2);
    EXPECT_FALSE(property1 != property2);
}

TEST(property_tests, double_test) {
    double number(42.0);
    property property1(number);
    EXPECT_EQ(property1.type(), property_type::NUMBER);
    EXPECT_TRUE(property1.is_valid());
    EXPECT_FALSE(property1.is_string());
    EXPECT_FALSE(property1.is_vector());
    EXPECT_FALSE(property1.is_bool());
    EXPECT_TRUE(property1.is_double());
    EXPECT_FALSE(property1.is_map());
    double number1;
    EXPECT_TRUE(property1.try_get_double(number1));
    EXPECT_EQ(number1, number);
    property property2(double(42.0));
    double number2;
    EXPECT_TRUE(property2.try_get_double(number2));
    EXPECT_EQ(number2, number);
    EXPECT_TRUE(property1 == property2);
    EXPECT_FALSE(property1 != property2);
}

TEST(property_tests, bool_test) {
    bool boolean(true);
    property property1(boolean);
    EXPECT_EQ(property1.type(), property_type::BOOLEAN);
    EXPECT_TRUE(property1.is_valid());
    EXPECT_FALSE(property1.is_string());
    EXPECT_FALSE(property1.is_vector());
    EXPECT_TRUE(property1.is_bool());
    EXPECT_FALSE(property1.is_double());
    EXPECT_FALSE(property1.is_map());
    bool boolean1;
    EXPECT_TRUE(property1.try_get_bool(boolean1));
    EXPECT_EQ(boolean1, boolean);
    property property2(bool(true));
    bool boolean2;
    EXPECT_TRUE(property2.try_get_bool(boolean2));
    EXPECT_EQ(boolean2, boolean);
    EXPECT_TRUE(property1 == property2);
    EXPECT_FALSE(property1 != property2);
}

TEST(property_tests, setters_test) {
    property property1;
    EXPECT_TRUE(property1.is_valid());
    EXPECT_FALSE(property1.is_vector());
    EXPECT_FALSE(property1.is_bool());
    EXPECT_TRUE(property1.is_double());
    EXPECT_FALSE(property1.is_map());
    EXPECT_FALSE(property1.is_string());
    bool boolean(true);
    property1.set_bool(boolean);
    EXPECT_EQ(property1.type(), property_type::BOOLEAN);
    EXPECT_TRUE(property1.is_valid());
    EXPECT_FALSE(property1.is_string());
    EXPECT_FALSE(property1.is_vector());
    EXPECT_TRUE(property1.is_bool());
    EXPECT_FALSE(property1.is_double());
    EXPECT_FALSE(property1.is_map());
    bool boolean1;
    EXPECT_TRUE(property1.try_get_bool(boolean1));
    EXPECT_EQ(boolean1, boolean);
    double number(42.0);
    property1.set_double(number);
    EXPECT_EQ(property1.type(), property_type::NUMBER);
    EXPECT_TRUE(property1.is_valid());
    EXPECT_FALSE(property1.is_string());
    EXPECT_FALSE(property1.is_vector());
    EXPECT_FALSE(property1.is_bool());
    EXPECT_TRUE(property1.is_double());
    EXPECT_FALSE(property1.is_map());
    double number1;
    EXPECT_TRUE(property1.try_get_double(number1));
    EXPECT_EQ(number1, number);
    property property2(double(42.0));
    double number2;
    EXPECT_TRUE(property2.try_get_double(number2));
    EXPECT_EQ(number2, number);
    std::string string("42");
    property1.set_string(string);
    EXPECT_EQ(property1.type(), property_type::STRING);
    EXPECT_TRUE(property1.is_valid());
    EXPECT_TRUE(property1.is_string());
    EXPECT_FALSE(property1.is_vector());
    EXPECT_FALSE(property1.is_bool());
    EXPECT_FALSE(property1.is_double());
    EXPECT_FALSE(property1.is_map());
    std::string string1;
    EXPECT_TRUE(property1.try_get_string(string1));
    EXPECT_EQ(string1, string);
}

TEST(property_tests, rvalue_setters_test) {
    property property;
    std::string string("42");
    std::string string1;
    property.set_string(string);
    EXPECT_TRUE(property.try_get_string(string1));
    EXPECT_EQ(string, string1);
    double number;
    double number1(42.0);
    property.set_double(double(42.0));
    EXPECT_TRUE(property.try_get_double(number));
    EXPECT_EQ(number, number1);
    bool boolean(true);
    bool boolean1;
    property.set_bool(bool(true));
    EXPECT_TRUE(property.try_get_bool(boolean1));
    EXPECT_EQ(boolean, boolean1);
}
// /TODO:: tests of array and table.