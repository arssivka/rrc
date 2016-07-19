/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once

#include "rrc/TSLookUp.h"
#include "rrc/Property.h"
#include <string>

namespace rrc {
    class Settings {
    public:

        Settings(unsigned num) : mSettings(num) { }

        Settings() {}

        void addOrUpdate(const std::string& key, Property&& data) {
            mSettings.set(key, std::move(data));
        }

        template <class D>
        void addOrUpdate(const std::string& key, D&& data) {
            mSettings.get(key)->setSetting(std::forward<D>(data));
        }

        void remove(const std::string& key) {
            mSettings.remove(key);
        }

        template <class T>
        T get(const std::string& key) {
            return mSettings.get(key)->getSetting();
        }


    private:
        TSLookUp<std::string, Property> mSettings;
    };
}


