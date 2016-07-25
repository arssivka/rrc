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
            mSettings.get(key)->set<D>(std::forward<D>(data));
        }

        void remove(const std::string& key) {
            mSettings.remove(key);
        }

        Property get(const std::string& key) const {
            return mSettings.get(key);
        }

        bool contains(const std::string& key) const {
            return mSettings.contains(key);
        }


    private:
        TSLookUp<std::string, Property> mSettings;
    };
}


