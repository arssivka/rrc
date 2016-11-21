/**
 *  @autor tekatod
 *  @date 9/26/16
 */
#pragma once


#include "Property.h"
#include "PropertyDictionary.h"
#include "Pointer.h"
#include <map>

namespace rrc {
    /**
     * @brief Abstract class for getting required up-to-date collection of settings from the SettingsHolder; also can get required property by it's name.
     */
    class AbstractPropertyListener : public Pointer<AbstractPropertyListener> {
    public:

        /**
         * @brief Returns property with the specified name.
         * @param propertyName Name of the required property.
         * @return Property Required property.
         */
        virtual Property getProperty(const std::string& propertyName) = 0;

        /**
         * @brief Sets the collection of settings to this listener
         * @param dictionary PropertyDictionary with the needed settings
         */
        virtual void setDictionary(PropertyDictionary dictionary) = 0;

        /**
         * @brief Returns collection of settings from this listener
         * @return PropertDictionary with the settings
         */
        virtual PropertyDictionary getDictionary() = 0;

        /**
         * @brief Checks if there is such Property with the specified name
         * @param propertyName Name of the needed property
         * @return True if such Property exists, otherwise false.
         */
        virtual bool isContainsName(const std::string &propertyName) = 0;

        /**
         * @brief Virtual destructor of AbstractPropertyListener
         */
        virtual ~AbstractPropertyListener() { }

    };
}