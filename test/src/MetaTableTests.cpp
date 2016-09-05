/**
 *  @autor tekatod
 *  @date 9/1/16
 */
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/core/MetaTable.h"
#include "Message.pb.h"

using namespace rrc;

TEST(MetaTableTest, RegisterTest) {
    MetaTable mtbl;
    EXPECT_TRUE(mtbl.registerTypeId<testmessages::TestMessage>(1u));
}

TEST(MetaTableTest, ReservedIdTest) {
    MetaTable mtbl;
    mtbl.registerTypeId<testmessages::TestMessage>(1u);
    EXPECT_TRUE(mtbl.isIdReserved(1u));
}

TEST(MetaTableTest, GetTypeIdTest1) {
    MetaTable mtbl;
    mtbl.registerTypeId<testmessages::TestMessage>(1);
    EXPECT_EQ(mtbl.getTypeId<testmessages::TestMessage>(), 1u);
}

TEST(MetaTableTest, GetTypeIdTest2) {
    MetaTable metaTable;
    metaTable.registerTypeId<testmessages::TestMessage>(1);
    metaTable.registerTypeId<testmessages::TestMessageContainer>(2);
    EXPECT_EQ(metaTable.getTypeId<testmessages::TestMessage>(), 1u);
    EXPECT_EQ(metaTable.getTypeId<testmessages::TestMessageContainer>(), 2u);
}

TEST(MetaTableTest, FreeIdTest) {
    MetaTable mtbl;
    mtbl.registerTypeId<testmessages::TestMessage>(1u);
    EXPECT_TRUE(mtbl.freeTypeId(1));
}

TEST(MetaTableTest, FreeIdReservedTest) {
    MetaTable mtbl;
    mtbl.registerTypeId<testmessages::TestMessage>(1u);
    mtbl.freeTypeId(1);
    EXPECT_FALSE(mtbl.isIdReserved(1));
}

TEST(MetaTableTest, ReplaceRegisteredId) {
    MetaTable metaTable;
    metaTable.registerTypeId<testmessages::TestMessage>(1u);
    EXPECT_FALSE(metaTable.registerTypeId<testmessages::TestMessageContainer>(1u));
}

TEST(MetaTableTest, GetUnregisteredId) {
    MetaTable metaTable;
    EXPECT_EQ(metaTable.getTypeId<testmessages::TestMessage>(),
              MetaTable::UNKNOWN_TYPE_ID);
}

TEST(MetaTableTest, MessageFactoryTest) {
    MetaTable metaTable;
    metaTable.registerTypeId<testmessages::TestMessage>(1u);
    MessageFactoryPtr messageFactoryPtr = metaTable.getMessageFactory(1u);
    ASSERT_NE(messageFactoryPtr, nullptr);
    EXPECT_NE(messageFactoryPtr->createMessage(), nullptr);
    EXPECT_EQ(metaTable.getMessageFactory(2u), nullptr);
}
