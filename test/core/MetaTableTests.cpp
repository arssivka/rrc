/**
 *  @autor tekatod
 *  @date 9/1/16
 */
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/MetaTable.h"
#include "Message.pb.h"

TEST(MetaTableTest, RegisterTest) {
    rrc::MetaTable mtbl;
    EXPECT_TRUE(mtbl.registerTypeId<message::TestMessage>(1u));
}

TEST(MetaTableTest, ReservedIdTest) {
    rrc::MetaTable mtbl;
    mtbl.registerTypeId<message::TestMessage>(1u);
    EXPECT_TRUE(mtbl.isIdReserved(1u));
}

TEST(MetaTableTest, GetTypeIdTest1) {
    rrc::MetaTable mtbl;
    mtbl.registerTypeId<message::TestMessage>(1);
    EXPECT_EQ(mtbl.getTypeId<message::TestMessage>(), 1u);
}

TEST(MetaTableTest, GetTypeIdTest2) {
    rrc::MetaTable metaTable;
    metaTable.registerTypeId<message::TestMessage>(1);
    metaTable.registerTypeId<message::TestMessageContainer>(2);
    EXPECT_EQ(metaTable.getTypeId<message::TestMessage>(), 1u);
    EXPECT_EQ(metaTable.getTypeId<message::TestMessageContainer>(), 2u);
}

TEST(MetaTableTest, FreeIdTest) {
    rrc::MetaTable mtbl;
    mtbl.registerTypeId<message::TestMessage>(1u);
    EXPECT_TRUE(mtbl.freeTypeId(1));
}

TEST(MetaTableTest, FreeIdReservedTest) {
    rrc::MetaTable mtbl;
    mtbl.registerTypeId<message::TestMessage>(1u);
    mtbl.freeTypeId(1);
    EXPECT_FALSE(mtbl.isIdReserved(1));
}

TEST(MetaTableTest, ReplaceRegisteredId) {
    rrc::MetaTable metaTable;
    metaTable.registerTypeId<message::TestMessage>(1u);
    EXPECT_FALSE(metaTable.registerTypeId<message::TestMessageContainer>(1u));
}

TEST(MetaTableTest, GetUnregisteredId) {
    rrc::MetaTable metaTable;
    EXPECT_EQ(metaTable.getTypeId<message::TestMessage>(),
              rrc::MetaTable::UNKNOWN_TYPE_ID);
}
