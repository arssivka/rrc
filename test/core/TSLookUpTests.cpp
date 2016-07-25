/**
 *  @autor tekatod
 *  @date 7/25/16
 */

#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "rrc/TSLookUp.h"
#include <thread>

TEST(set_get_test, setter_test) {
    rrc::TSLookUp testlkp;
    class nagrebator {
    public:
        void operator() (rrc::TSLookUp& vstav) {
            std::string name = "first";
            vstav.set()

        }
    };

}