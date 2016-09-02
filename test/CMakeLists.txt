enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
        core/PropertyTests.cpp
        core/SettingsTests.cpp
        core/TSLookUpTests.cpp
        core/MessageTests.cpp
        core/MetaTableTests.cpp
        core/TopicTest.cpp
        modules/BigTests.cpp core/MessageListenerTests.cpp core/BillboardTests.cpp core/RecieveGuardTests.cpp)

set(PROTOS
        proto/Message.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})


add_executable(tests ${SRCS} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(tests gtest gtest_main rrc ${PROTOBUF_LIBRARIES})
target_include_directories(tests PUBLIC ${PROTOBUF_INCLUDE_DRIS})

