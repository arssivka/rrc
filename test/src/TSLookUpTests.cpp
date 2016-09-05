/**
 *  @autor tekatod
 *  @date 7/25/16
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/core/TSLookUp.h"
#include <thread>

using namespace rrc;

TEST(TSLookUpTest, ContainsTest) {
    TSLookUp<std::string, bool> testlkp;
    testlkp.set("test", true);
    EXPECT_TRUE(testlkp.contains("test"));
}

TEST(TSLookUpTest, SetterTest) {
    TSLookUp<std::string, int> testlkp;

    std::thread nagrebator1([&]() {
        std::string names[] = {"first", "second"};
        for (int i = 0; i < 2; ++i) {
            testlkp.set(names[i], i);
        }
    });

    std::thread nagrebator2([&]() {
        std::string names[] = {"second_first", "second_second"};
        for (int i = 0; i < 2; ++i) {
            testlkp.set(names[i], i);
        }
    });

    nagrebator1.join();
    nagrebator2.join();

    EXPECT_TRUE((testlkp.contains("first") && testlkp.contains("second") &&
            testlkp.contains("second_first") && testlkp.contains("second_second")));
}

TEST(TSLookUpTest, GetterTest) {
    TSLookUp<std::string, int> testlkp;

    std::string names[] = {"first", "second"};

    for(int i = 0; i < 2; ++i) {
        testlkp.set(names[i], i);
    }

    int expect1 = 0;
    int expect2 = 0;

    std::thread razgrebator1([&]() {
        for(int i = 0; i < 2; ++i) {
            if(testlkp.contains(names[i])) {
                expect1 += *testlkp.get(names[i]).get();
            }
        }
    });

    std::thread razgrebator2([&]() {
        for(int i = 0; i < 2; ++i) {
            if(testlkp.contains(names[i])) {
                expect2 += *testlkp.get(names[i]).get();
            }
        }
    });

    razgrebator1.join();
    razgrebator2.join();

    EXPECT_TRUE((expect1 == expect2) && expect1 != 0 && expect2 != 0);
}

//TEST(set_get_test, getter_setter_test) {
//    TSLookUp<std::string, int> testlkp;
//
//    std::string names[] = {"first", "second"};
//
//    for(int i = 0; i < 3; ++i) {
//        testlkp.set(names[i], i);
//    }
//
//    int expect1 = 0;
//
//    std::thread razgrebator1([&]() {
//        for(int i = 0; i < 2; ++i) {
//            if(testlkp.contains(names[i])) {
//                expect1 += *testlkp.get(names[i]).get();
//            }
//        }
//    });
//
//    std::thread nagrebator1([&]() {
//        testlkp.set("nagrebator_insert", 42);
//        testlkp.set("nagrebator_insert2", 42);
//    });
//
//    razgrebator1.join();
//    nagrebator1.join();
//
//    EXPECT_TRUE((expect1 == 3 && testlkp.contains("nagrebator_insert") &&
//            testlkp.contains("nagrebator_insert2")));
//}

TEST(TSLookUpTest, OneRemover) {
    TSLookUp<std::string, bool> testlkp;
    testlkp.set("test", true);
    testlkp.remove("test");
    EXPECT_FALSE(testlkp.contains("test"));
}

TEST(TSLookUpTest, TwoRemovers) {
    TSLookUp<std::string, bool> testlkp;
    testlkp.set("test", true);
    testlkp.set("test2", true);

    std::thread remover1([&]() {
        testlkp.remove("test");
    });
    std::thread remover2([&]() {
        testlkp.remove("test2");
    });

    remover1.join();
    remover2.join();

    EXPECT_FALSE((testlkp.contains("test") && testlkp.contains("test2")));
}

TEST(TSLookUpTest, OneDetacher) {
    TSLookUp<std::string, bool> testlkp;
    testlkp.set("test", true);
    bool tst = testlkp.detach("test").get();
    EXPECT_FALSE((testlkp.contains("test") && !tst));
}