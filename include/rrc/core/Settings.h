/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once

#include <string>
#include "TSLookUp.h"
#include "Property.h"

namespace rrc {
    class Settings {
    public:

        /**
         * @brief Constructor of settings.
         * @param num Number of prereserved cells for settings
         */
        Settings(unsigned num);

        /**
         * @brief Default constructor of settins
         */
        Settings();

        /**
         * @brief Stores setting to container
         * @param key Key of the setting
         * @param data Data to store of string, int, bool, float or Property type
         */
        template <class D>
        void set(const std::string& key, D&& data) {
            mSettings.set(key, Property(std::forward<D>(data)));
        }

        /**
         * @brief Removes the setting for the specified key
         * @param key Key of setting to remove
         */
        void remove(const std::string& key);

        /**
         * @brief Returns setting by the specified key
         * @param key Key of desired setting
         * @return Property
         */
        Property get(const std::string& key) const;

        /**
         * @brief Checks if there is a setiing with the specified key
         * @param key Key to check
         * @return True if such setting in the container, otherwise false
         */
        bool contains(const std::string& key) const;


    private:
        TSLookUp<std::string, Property> mSettings;
    };
}


