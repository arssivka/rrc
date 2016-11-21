/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#pragma once


#include "AbstractPropertyListener.h"
#include "TaskQueueWrapper.h"
#include "SettingsHolder.h"
#include "Mechanism.h"

namespace rrc {
    class SettingsMechanism : public Mechanism {
    public:
        SettingsMechanism(const TaskQueueWrapper& syncQueue, SettingsHolder::Ptr& settingsHolder);


        /**
         * @brief Registers property listener for the dictionary with the specified name
         * @param dictionaryName Name of the dictionary for the listener
         * @param listener Pointer to listener taht needs to be registered
         */
        void addSettingsListener(const std::string& dictionaryName, AbstractPropertyListener::Ptr listener);

        /**
         * @brief Unregisters property listener for the dictionary with the specified name
         * @param dictionaryName Name of the dictionary for the listener
         * @param listener Pointer to listener taht needs to be unregistered
         */
        void removeSettingsListener(const std::string& dictionaryName, AbstractPropertyListener::Ptr listener);

        auto getNames() const noexcept;

    private:
        TaskQueueWrapper mSyncQueue;
        SettingsHolder::Ptr mSettingsHolder;
    };
}


