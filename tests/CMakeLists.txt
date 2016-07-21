    enable_testing()

    #    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    set(BASIC_TEST_SRCS
            tests/basic/PropertyTests.cpp)

    set(ADVANCED_TEST_SRCS
            tests/advanced/BigTests)

    add_executable(runBTests BASIC_TEST_SRCS)
    target_link_libraries(runBTests gtest gtest_main rrc)

    add_executable(runATests ADVANCED_TEST_SRCS)
    target_link_libraries(runATests gtest gtest_main rrc)

    add_test(NAME rrc-Basic-Testing runTests)
    add_test(NAME rrc-Advanced-Testing runTests)
