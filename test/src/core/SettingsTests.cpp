///**
// *  @autor tekatod
// *  @date 7/22/16
// */
//
//#include <iostream>
//#include <string>
//#include <gtest/gtest.h>
//#include "rrc/core/SettingsBillboard.h"
//#include "rrc/core/PropertyListener.h"
//
//using namespace rrc;
//
//class SettingsFixture : public ::testing::Test {
//public:
//    SettingsFixture()
//            : mProperty1(42), mProperty2(true), mProperty3("42") { }
//
//protected:
//    Settings mSettings;
//    Property mProperty1;
//    Property mProperty2;
//    Property mProperty3;
//};
//
//TEST_F(SettingsFixture, AddRemovePropertyTests) {
//    mSettings.addOrUpdateProperty("test1", mProperty1);
//    mSettings.addOrUpdateProperty("test2", mProperty2);
//    mSettings.addOrUpdateProperty("test3", mProperty3);
//    EXPECT_TRUE(mSettings.contains("test1"));
//    EXPECT_TRUE(mSettings.contains("test2"));
//    EXPECT_TRUE(mSettings.contains("test3"));
//    mSettings.removeProperty("test1");
//    mSettings.removeProperty("test2");
//    mSettings.removeProperty("test3");
//    EXPECT_FALSE(mSettings.contains("test1"));
//    EXPECT_FALSE(mSettings.contains("test2"));
//    EXPECT_FALSE(mSettings.contains("test3"));
//}
//
//TEST_F(SettingsFixture, GetKeysTest) {
//    mSettings.addOrUpdateProperty("test1", mProperty1);
//    mSettings.addOrUpdateProperty("test2", mProperty2);
//    mSettings.addOrUpdateProperty("test3", mProperty3);
//    auto mSet = mSettings.getKeys();
//    EXPECT_TRUE(mSet.find("test1") != mSet.end());
//    EXPECT_TRUE(mSet.find("test2") != mSet.end());
//    EXPECT_TRUE(mSet.find("test3") != mSet.end());
//}
//
//TEST_F(SettingsFixture, AddRemoveListenerTest) {
//    mSettings.addOrUpdateProperty("test1", mProperty1);
//    mSettings.addOrUpdateProperty("test2", mProperty2);
//    mSettings.addOrUpdateProperty("test3", mProperty3);
//    PropertyListenerPtr mPropertyListener1 = std::make_shared<PropertyListener>();
//    PropertyListenerPtr mPropertyListener2 = std::make_shared<PropertyListener>();
//    PropertyListenerPtr mPropertyListener3 = std::make_shared<PropertyListener>();
//    mSettings.addListener("test1", mPropertyListener1);
//    mSettings.addListener("test2", mPropertyListener2);
//    mSettings.addListener("test3", mPropertyListener3);
//    EXPECT_TRUE(mSettings.hasListeners("test1"));
//    EXPECT_TRUE(mSettings.hasListeners("test2"));
//    EXPECT_TRUE(mSettings.hasListeners("test3"));
//    mSettings.removeListener("test1", mPropertyListener1);
//    mSettings.removeListener("test2", mPropertyListener2);
//    mSettings.removeListener("test3", mPropertyListener3);
//    EXPECT_FALSE(mSettings.hasListeners("test1"));
//    EXPECT_FALSE(mSettings.hasListeners("test2"));
//    EXPECT_FALSE(mSettings.hasListeners("test3"));
//}
////
//TEST_F(SettingsFixture, GetDataFromListenersUpdateTest) {
//    mSettings.addOrUpdateProperty("test1", mProperty1);
//    mSettings.addOrUpdateProperty("test2", mProperty2);
//    mSettings.addOrUpdateProperty("test3", mProperty3);
//    PropertyListenerPtr mPropertyListener1 = std::make_shared<PropertyListener>();
//    PropertyListenerPtr mPropertyListener2 = std::make_shared<PropertyListener>();
//    PropertyListenerPtr mPropertyListener3 = std::make_shared<PropertyListener>();
//    mSettings.addListener("test1", mPropertyListener1);
//    mSettings.addListener("test2", mPropertyListener2);
//    mSettings.addListener("test3", mPropertyListener3);
//    EXPECT_EQ(42, mPropertyListener1->getProperty().getInt());
//    EXPECT_EQ(true, mPropertyListener2->getProperty().getBool());
//    EXPECT_EQ("42", mPropertyListener3->getProperty().getString());
//    mSettings.addOrUpdateProperty("test1", 41);
//    mSettings.addOrUpdateProperty("test2", false);
//    mSettings.addOrUpdateProperty("test3", "41");
//    EXPECT_EQ(41, mPropertyListener1->getProperty().getInt());
//    EXPECT_EQ(false, mPropertyListener2->getProperty().getBool());
//    EXPECT_EQ("41", mPropertyListener3->getProperty().getString());
//}