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
    EXPECT_TRUE(mtbl.registerTypeId<message::TestMessage>(1));
}

TEST(MetaTableTest, ReservedIdTest) {
    rrc::MetaTable mtbl;
    mtbl.registerTypeId<message::TestMessage>(1);
    EXPECT_TRUE(mtbl.isIdReserved(1));
}

TEST(MetaTableTest, GetTypeIdTest) {
    rrc::MetaTable mtbl;
    mtbl.registerTypeId<message::TestMessage>(1);
    EXPECT_EQ(mtbl.getTypeId<message::TestMessage>(), (unsigned int) 1);
}

TEST(MetaTableTest, GetSizeByIdTest) {
    rrc::MetaTable mtbl;
    mtbl.registerTypeId<message::TestMessage>(1);
    EXPECT_EQ(sizeof(message::TestMessage), mtbl.getTypeSizeById((unsigned int) 1));
}

TEST(MetaTableTest, FreeIdTest) {
    rrc::MetaTable mtbl;
    mtbl.registerTypeId<message::TestMessage>(1);
    EXPECT_TRUE(mtbl.freeTypeId((unsigned int) 1));
}

TEST(MetaTableTest, FreeIdReservedTest) {
    rrc::MetaTable mtbl;
    mtbl.registerTypeId<message::TestMessage>(1);
    mtbl.freeTypeId(1);
    EXPECT_FALSE(mtbl.isIdReserved(1));
}