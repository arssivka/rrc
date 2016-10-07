/**
 *  @autor tekatod
 *  @date 7/22/16
 */

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rrc/core/SettingsHolder.h"
#include "rrc/core/PropertyListener.h"

using namespace rrc;

class SettingsFixture : public ::testing::Test {
public:
    SettingsFixture()
            : mProperty1(42), mProperty2(true), mProperty3("42") { }

protected:
    SettingsHolder mSettings;
    Property mProperty1;
    Property mProperty2;
    Property mProperty3;
};

TEST_F(SettingsFixture, AddRemoveTests) {
    EXPECT_TRUE(mSettings.empty());
    EXPECT_FALSE(mSettings.hasDictionary("testdict1"));
    EXPECT_FALSE(mSettings.hasDictionary("testdict2"));
    mSettings.addOrUpdateProperty("testdict1","test1", mProperty1);
    mSettings.addOrUpdateProperty("testdict1", "test2", mProperty2);
    mSettings.addOrUpdateProperty("testdict2", "test3", mProperty3);
    EXPECT_TRUE(mSettings.hasDictionary("testdict1"));
    EXPECT_TRUE(mSettings.hasDictionary("testdict2"));
    EXPECT_TRUE(mSettings.isDictionaryContainsProperty("testdict1", "test1"));
    EXPECT_TRUE(mSettings.isDictionaryContainsProperty("testdict1", "test2"));
    EXPECT_TRUE(mSettings.isDictionaryContainsProperty("testdict2", "test3"));
    mSettings.removeProperty("testdict1", "test1");
    mSettings.removeProperty("testdict1", "test2");
    mSettings.removeProperty("testdict2", "test3");
    EXPECT_FALSE(mSettings.isDictionaryContainsProperty("testdict1", "test1"));
    EXPECT_FALSE(mSettings.isDictionaryContainsProperty("testdict1", "test2"));
    EXPECT_FALSE(mSettings.isDictionaryContainsProperty("testdict2", "test3"));
    mSettings.removeDictionary("testdict2");
    EXPECT_FALSE(mSettings.hasDictionary("testdict2"));
}

TEST_F(SettingsFixture, GetKeysTests) {
    EXPECT_TRUE(mSettings.getKeys().empty());
    mSettings.addOrUpdateProperty("testdict1","test1", mProperty1);
    mSettings.addOrUpdateProperty("testdict1", "test2", mProperty2);
    mSettings.addOrUpdateProperty("testdict2", "test3", mProperty3);
    EXPECT_FALSE(mSettings.getKeys().empty());
    EXPECT_FALSE(mSettings.getDictionaryKeys("testdict1").empty());
    EXPECT_FALSE(mSettings.getDictionaryKeys("testdict2").empty());
    EXPECT_TRUE(mSettings.getDictionaryKeys("notexisting").empty());
}

TEST_F(SettingsFixture, AddRemoveListenerTest) {
    mSettings.addOrUpdateProperty("testdict1", "test1", mProperty1);
    mSettings.addOrUpdateProperty("testdict1", "test2", mProperty2);
    mSettings.addOrUpdateProperty("testdict2", "test3", mProperty3);
    PropertyListenerPtr mPropertyListener1 = std::make_shared<PropertyListener>();
    PropertyListenerPtr mPropertyListener2 = std::make_shared<PropertyListener>();
    PropertyListenerPtr mPropertyListener3 = std::make_shared<PropertyListener>();
    mSettings.addListener("testdict1", mPropertyListener1);
    mSettings.addListener("testdict1", mPropertyListener2);
    mSettings.addListener("testdict2", mPropertyListener3);
    EXPECT_TRUE(mSettings.isDictionaryHasListeners("testdict1"));
    EXPECT_TRUE(mSettings.isDictionaryHasListeners("testdict2"));
    mSettings.removeListener("testdict1", mPropertyListener1);
    mSettings.removeListener("testdict1", mPropertyListener2);
    EXPECT_FALSE(mSettings.isDictionaryHasListeners("testdict1"));
    EXPECT_TRUE(mSettings.isDictionaryHasListeners("testdict2"));
    mSettings.removeListener("testdict2", mPropertyListener3);
    EXPECT_FALSE(mSettings.isDictionaryHasListeners("testdict2"));
}

TEST_F(SettingsFixture, GetDataFromListenersAndUpdateTests) {
    mSettings.addOrUpdateProperty("testdict1", "test1", mProperty1);
    mSettings.addOrUpdateProperty("testdict1", "test2", mProperty2);
    mSettings.addOrUpdateProperty("testdict2", "test3", mProperty3);
    PropertyListenerPtr mPropertyListener1 = std::make_shared<PropertyListener>();
    PropertyListenerPtr mPropertyListener2 = std::make_shared<PropertyListener>();
    PropertyListenerPtr mPropertyListener3 = std::make_shared<PropertyListener>();
    mSettings.addListener("testdict1", mPropertyListener1);
    mSettings.addListener("testdict1", mPropertyListener2);
    mSettings.addListener("testdict2", mPropertyListener3);
    EXPECT_EQ(42, mPropertyListener1->getProperty("test1").getInt());
    EXPECT_EQ(42, mPropertyListener2->getProperty("test1").getInt());
    EXPECT_EQ(true, mPropertyListener1->getProperty("test2").getInt());
    EXPECT_EQ(true, mPropertyListener2->getProperty("test2").getBool());
    EXPECT_EQ("42", mPropertyListener3->getProperty("test3").getString());
    mSettings.addOrUpdateProperty("testdict1", "test1", 41);
    mSettings.addOrUpdateProperty("testdict1", "test2", false);
    mSettings.addOrUpdateProperty("testdict2", "test3", "41");
    EXPECT_EQ(41, mPropertyListener1->getProperty("test1").getInt());
    EXPECT_EQ(41, mPropertyListener2->getProperty("test1").getInt());
    EXPECT_EQ(false, mPropertyListener1->getProperty("test2").getInt());
    EXPECT_EQ(false, mPropertyListener2->getProperty("test2").getBool());
    EXPECT_EQ("41", mPropertyListener3->getProperty("test3").getString());
}

TEST_F(SettingsFixture, EmptyDictionaryTests) {
    mSettings.addOrUpdateProperty("testdict1", "test1", mProperty1);
    mSettings.addOrUpdateProperty("testdict1", "test2", mProperty2);
    mSettings.removeProperty("testdict1", "test1");
    mSettings.removeProperty("testdict1", "test2");
    EXPECT_TRUE(mSettings.isDictionaryEmpty("testdict1"));
}