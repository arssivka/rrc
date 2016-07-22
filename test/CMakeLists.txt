    enable_testing()

    set(SRCS
            core/PropertyTests.cpp
            core/SettingsTests.cpp
            modules/BigTests.cpp)

    add_executable(tests ${SRCS})
    add_test(NAME rrc-tests tests)
    target_link_libraries(tests gtest gtest_main rrc)

