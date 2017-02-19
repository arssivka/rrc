/**
 *  @autor tekatod
 *  @date 2/16/17
 */

#include <gtest/gtest.h>
#include <rrc/core/Array.h>

using namespace rrc;

TEST(ArrayTests, ReserveResizeTests) {
    Array array;
    array.reserve(5);
    array.push(Property(Boolean(true)));
    array.push(Property(Boolean(true)));
    array.push(Property(Boolean(true)));
    array.push(Property(Boolean(true)));
    array.push(Property(Boolean(true)));
    EXPECT_EQ(array.getSize(), (size_t) 5);
    array.resize(3);
    EXPECT_EQ(array.getSize(), (size_t) 3);
}

TEST(ArrayTests, EmptyTests) {
    Array array;
    EXPECT_TRUE(array.isEmpty());
    array.push(Property(Boolean(true)));
    EXPECT_FALSE(array.isEmpty());
}

TEST(ArrayTests, LValuePushGetTests) {
    Array array;
    Property property1(String("1"));
    Property property2(Boolean(true));
    Property property3(Number(42.0));
    Property property4;
    Property property5;
    Property property6;
    Property property7;
    array.push(property1);
    array.push(property2);
    array.push(property3);
    EXPECT_EQ(array[0], property1);
    EXPECT_EQ(array[1], property2);
    EXPECT_EQ(array[2], property3);
    EXPECT_EQ(array.get(0), property1);
    EXPECT_EQ(array.get(1), property2);
    EXPECT_EQ(array.get(2), property3);
    EXPECT_EQ(array.get(3).isNil(), property4.isNil());
    array.tryGet(0, property5);
    array.tryGet(1, property6);
    array.tryGet(2, property7);
    EXPECT_EQ(property5, property1);
    EXPECT_EQ(property6, property2);
    EXPECT_EQ(property7, property3);
}

TEST(ArrayTests, RValuePushGetTests) {
    Array array;
    Property property1(String("1"));
    Property property2(Boolean(true));
    Property property3(Number(42.0));
    Property property4;
    Property property5;
    Property property6;
    Property property7;
    array.push(Property(String("1")));
    array.push(Property(Boolean(true)));
    array.push(Property(Number(42.0)));
    EXPECT_EQ(array[0], property1);
    EXPECT_EQ(array[1], property2);
    EXPECT_EQ(array[2], property3);
    EXPECT_EQ(array.get(0), property1);
    EXPECT_EQ(array.get(1), property2);
    EXPECT_EQ(array.get(2), property3);
    EXPECT_EQ(array.get(3).isNil(), property4.isNil());
    array.tryGet(0, property5);
    array.tryGet(1, property6);
    array.tryGet(2, property7);
    EXPECT_EQ(property5, property1);
    EXPECT_EQ(property6, property2);
    EXPECT_EQ(property7, property3);
}

TEST(ArrayTests, SetTests) {
    Array array;
    array.push(Property(Boolean(true)));
    array.push(Property(Boolean(true)));
    array.push(Property(Boolean(true)));
    array.push(Property(Boolean(true)));
    array.push(Property(Boolean(true)));
    array.push(Property(Boolean(true)));
    Property property1(String("1"));
    Property property2(Boolean(true));
    Property property3(Number(42.0));
    array.set(0, property1);
    array.set(1, property2);
    array.set(2, property3);
    array.set(3, Property(String("1")));
    array.set(4, Property(Boolean(true)));
    array.set(5, Property(Number(42.0)));
    EXPECT_EQ(array[0], property1);
    EXPECT_EQ(array[1], property2);
    EXPECT_EQ(array[2], property3);
    EXPECT_EQ(array[3], property1);
    EXPECT_EQ(array[4], property2);
    EXPECT_EQ(array[5], property3);
}

TEST(ArrayTests, PopTests) {
    Array array;
    array.push(Property(Boolean(false)));
    array.push(Property(Boolean(false)));
    array.push(Property(Boolean(true)));
    Property aProperty = array.pop();
    EXPECT_EQ(aProperty, Property(Boolean(true)));
    EXPECT_EQ(array.getSize(), (size_t) 2);
}

TEST(ArrayTests, EraseTests) {
    Array array;
    array.push(Property(Boolean(false)));
    array.push(Property(Boolean(false)));
    array.push(Property(Boolean(true)));
    array.erase(1);
    EXPECT_EQ(array[1], Property(Boolean(true)));
    EXPECT_EQ(array[0], Property(Boolean(false)));
    EXPECT_EQ(array.getSize(), (size_t) 2);
}

TEST(ArrayTests, RecurssiveTests) {
    Array array;
    Array array1;
    Array array2;
    Array array3;
    array1.push(Property(String("1")));
    array1.push(Property(Boolean(true)));
    array1.push(Property(Number(42.0)));
    array2.push(Property(String("1")));
    array2.push(Property(Boolean(true)));
    array2.push(Property(Number(42.0)));
    array3.push(Property(String("2")));
    array3.push(Property(Boolean(true)));
    array3.push(Property(Number(422.0)));
    array.push(Property(array1));
    array.push(Property(array2));
    array.push(Property(array3));
    EXPECT_EQ(array[0], Property(array1));
    EXPECT_EQ(array[1], Property(array2));
    EXPECT_EQ(array[2], Property(array3));
}

TEST(ArrayTests, OperatorsTests) {
    Array array1;
    Array array2;
    Array array3;
    array1.push(Property(String("1")));
    array1.push(Property(Boolean(true)));
    array1.push(Property(Number(42.0)));
    array2.push(Property(String("1")));
    array2.push(Property(Boolean(true)));
    array2.push(Property(Number(42.0)));
    array3.push(Property(String("2")));
    array3.push(Property(Boolean(true)));
    array3.push(Property(Number(422.0)));
    std::vector<Property> vector1{Property(String("1")), Property(Boolean(true)), Property(Number(42.0))};
    std::vector<Property> vector2{Property(String("1")), Property(Boolean(true)), Property(Number(42.0))};
    std::vector<Property> vector3{Property(String("2")), Property(Boolean(true)), Property(Number(422.0))};
    EXPECT_EQ(array1 == array2, vector1 == vector2);
    EXPECT_EQ(array1 != array3, vector1 != vector3);
    EXPECT_EQ(array1 != array2, vector1 != vector2);
    EXPECT_EQ(array1 > array3, vector1 > vector3);
    EXPECT_EQ(array1 < array3, vector1 < vector3);
    EXPECT_EQ(array1 <= array3, vector1 <= vector3);
    EXPECT_EQ(array1 >= array3, vector1 >= vector3);
}