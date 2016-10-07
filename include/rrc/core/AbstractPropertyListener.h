/**
 *  @autor tekatod
 *  @date 9/26/16
 */
#pragma once

#include "Property.h"
#include "PropertyDictionary.h"
#include <map>

namespace rrc {
    /**
     * @brief Abstract class for getting needed up-to-date collection of settings from the settings billboard; also can get needed property by it's name
     */
    class AbstractPropertyListener {
    public:

        /**
         * @brief Returns property with the specified name
         * @param key Name of the needed property
         * @return Property
         */
        virtual Property getProperty(const std::string& key) = 0;

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
         * @param key Name of the needed property
         * @return True if such Property exists, otherwise false.
         */
        virtual bool contains(const std::string& key) = 0;

        /**
         * @brief Virtual destructor of AbstractPropertyListener
         */
        virtual ~AbstractPropertyListener() { }

    };

    typedef std::shared_ptr<AbstractPropertyListener> AbstractPropertyListenerPtr;
}