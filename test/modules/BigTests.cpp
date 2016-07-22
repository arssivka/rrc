/**
 *  @autor tekatod
 *  @date 7/21/16
 */

#include <iostream>
#include "gtest/gtest.h"

class ExampleFixture : public ::testing::Test {
public:
    ExampleFixture() {
        //initialize all the good members
        gM = 42;
    }
    ~ExampleFixture() {
        //Destroy all the good members
    }
    // a lot of very good members
    int gM;
};

//use class for test!
TEST_F(ExampleFixture, example_check) {
    int ch = gM;
    EXPECT_EQ(42, ch);

}