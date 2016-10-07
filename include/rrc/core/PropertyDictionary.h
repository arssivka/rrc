/**
 *  @autor tekatod
 *  @date 10/7/16
 */
#pragma once

#include "CopyOnWrite.h"
#include "Property.h"
#include <map>

namespace rrc {
    /**
     * @brief This is a wrapper class of CopyOnWrite<std::map<string, Property>>. This is created to ease usage.
     */
    class PropertyDictionary {
    public:

        /**
         * @brief Default constructor of PropertyDictionary.
         */
        PropertyDictionary() = default;

        /**
         * @brief Default move constructor of PropertyDictionary.
         * @param other Another PropertyDictionary instance to move from.
         */
        PropertyDictionary(PropertyDictionary&& other) = default;

        /**
         * @brief Default copy constructor of PropertyDictionary.
         * @param other Another PropertyDictionary instance to copy from.
         */
        PropertyDictionary(const PropertyDictionary& other) = default;

        /**
         * @brief Constrcutor for creating PropertyDictionary.
         * @param dictionary CopyOnWrite<map<string, Property>> property collection.
         */
        PropertyDictionary(rrc::CopyOnWrite<std::map<std::string, rrc::Property>> dictionary);

        /**
         * @brief Method for setting the settings collection into dictionary.
         * @param dictionary CopyOnWrite<map<string, Property>> property collection.
         */
        void setDictionary(rrc::CopyOnWrite<std::map<std::string, rrc::Property>> dictionary);

        /**
         * @brief Checks if this PropertyDictionary contains Property with specified name.
         * @param key Name of the Property to check.
         * @return True if contains, otherwise false.
         */
        bool contains(const std::string key) const;

        /**
         * @brief Returns Property with specified name.
         * @param key Name of the property to get.
         * @return Property named with the specified key.
         */
        rrc::Property getProperty(const std::string& key);

        PropertyDictionary& operator= (const PropertyDictionary& other) = default;
        PropertyDictionary& operator= (PropertyDictionary&& other) = default;

    private:
        rrc::CopyOnWrite<std::map<std::string, rrc::Property>> mDictionary;
    };
}

