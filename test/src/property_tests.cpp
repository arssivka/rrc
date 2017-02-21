/**
 *  @autor tekatod
 *  @date 7/21/16
 */

#include <gtest/gtest.h>
#include <rrc/core.h>

using namespace rrc;


TEST(property_tests, string) {
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

TEST(property_tests, number) {
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

TEST(property_tests, boolean) {
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

TEST(property_tests, setters) {
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

TEST(property_tests, rvalue_setters) {
    property property1;
    std::string string("42");
    std::string string1;
    property1.set_string(string);
    EXPECT_TRUE(property1.try_get_string(string1));
    EXPECT_EQ(string, string1);
    double number;
    double number1(42.0);
    property1.set_double(double(42.0));
    EXPECT_TRUE(property1.try_get_double(number));
    EXPECT_EQ(number, number1);
    bool boolean(true);
    bool boolean1;
    property1.set_bool(bool(true));
    EXPECT_TRUE(property1.try_get_bool(boolean1));
    EXPECT_EQ(boolean, boolean1);
}

TEST(property_tests, vector) {
    std::vector<property> vector1;
    std::vector<property> vector2;
    property property1(vector1);
    EXPECT_TRUE(property1.is_valid());
    EXPECT_TRUE(property1.is_vector());
    EXPECT_FALSE(property1.is_bool());
    EXPECT_FALSE(property1.is_double());
    EXPECT_FALSE(property1.is_map());
    EXPECT_FALSE(property1.is_string());
    EXPECT_TRUE(property1.try_get_vector(vector2));
    EXPECT_EQ(vector2, vector1);
    property property2;
    property2.set_vector(std::vector<property>{property(std::string("42")), property(std::string("42"))});
    std::vector<property> vector3{property(std::string("42")), property(std::string("42"))};
    EXPECT_TRUE(property2.is_valid());
    EXPECT_TRUE(property2.is_vector());
    EXPECT_FALSE(property2.is_bool());
    EXPECT_FALSE(property2.is_double());
    EXPECT_FALSE(property2.is_map());
    EXPECT_FALSE(property2.is_string());
    EXPECT_TRUE(property2.try_get_vector(vector2));
    EXPECT_EQ(vector3, vector2);
    property property3;
    property3.set_vector(vector3);
    EXPECT_TRUE(property2.is_valid());
    EXPECT_TRUE(property2.is_vector());
    EXPECT_FALSE(property2.is_bool());
    EXPECT_FALSE(property2.is_double());
    EXPECT_FALSE(property2.is_map());
    EXPECT_FALSE(property2.is_string());
    EXPECT_TRUE(property3.try_get_vector(vector2));
    EXPECT_EQ(vector3, vector2);
}

TEST(property_tests, map) {
    std::unordered_map<std::string, property> map1;
    std::unordered_map<std::string, property> map2;
    property property1(map1);
    EXPECT_TRUE(property1.is_valid());
    EXPECT_FALSE(property1.is_vector());
    EXPECT_FALSE(property1.is_bool());
    EXPECT_FALSE(property1.is_double());
    EXPECT_TRUE(property1.is_map());
    EXPECT_FALSE(property1.is_string());
    EXPECT_TRUE(property1.try_get_map(map2));
    EXPECT_EQ(map2, map1);
    property property2;
    property2.set_map(std::unordered_map<std::string, property>{std::pair<std::string, property>(std::string("x"),
                                                                                                 property(std::string("42"))),
                                                                std::pair<std::string, property>(std::string("x"),
                                                                                                 property(std::string("42")))});
    std::unordered_map<std::string, property> map3{std::pair<std::string, property>(std::string("x"),
                                                                                    property(std::string("42"))),
                                                   std::pair<std::string, property>(std::string("x"),
                                                                                    property(std::string("42")))};
    EXPECT_TRUE(property2.is_valid());
    EXPECT_FALSE(property2.is_vector());
    EXPECT_FALSE(property2.is_bool());
    EXPECT_FALSE(property2.is_double());
    EXPECT_TRUE(property2.is_map());
    EXPECT_FALSE(property2.is_string());
    EXPECT_TRUE(property2.try_get_map(map2));
    EXPECT_EQ(map3, map2);
    property property3;
    property3.set_map(map3);
    EXPECT_TRUE(property2.is_valid());
    EXPECT_FALSE(property2.is_vector());
    EXPECT_FALSE(property2.is_bool());
    EXPECT_FALSE(property2.is_double());
    EXPECT_TRUE(property2.is_map());
    EXPECT_FALSE(property2.is_string());
    EXPECT_TRUE(property3.try_get_map(map2));
    EXPECT_EQ(map3, map2);
}