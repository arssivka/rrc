/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#include "include/rrc/core/SettingsMechanism.h"


rrc::SettingsMechanism::SettingsMechanism(const rrc::TaskQueueWrapper& syncQueue,
                                          rrc::Pointer<rrc::SettingsHolder>::Ptr& settingsHolder)
        : Mechanism("rrc.settings", 0), mSyncQueue(syncQueue), mSettingsHolder(std::move(settingsHolder)) {}


void rrc::SettingsMechanism::addSettingsListener(const std::string& dictionaryName,
                                                 rrc::Pointer<rrc::AbstractPropertyListener>::Ptr listener) {
    // TODO: Move to enclosure
    auto settingsHolder = mSettingsHolder;
    mSyncQueue.enqueue([settingsHolder, dictionaryName, listener]() {
        settingsHolder->addListener(dictionaryName, listener);
    });
}


void rrc::SettingsMechanism::removeSettingsListener(const std::string& dictionaryName,
                                                    rrc::Pointer<rrc::AbstractPropertyListener>::Ptr listener) {
    // TODO: Move to enclosure
    auto settingsHolder = mSettingsHolder;
    mSyncQueue.enqueue([settingsHolder, dictionaryName, listener]() {
        settingsHolder->removeListener(dictionaryName, listener);
    });
}


auto rrc::SettingsMechanism::getNames() const noexcept {
    return mSettingsHolder->getNames();
}
