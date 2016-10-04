/**
 *  @autor tekatod
 *  @date 9/26/16
 */
#pragma once

#include "Property.h"
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
        virtual Property getProperty(std::string key) = 0;

        /**
         * @brief Sets the collection of settings to this listener
         * @param dictionary CopyOnWrite map with the needed settings
         */
        virtual void setDictionary(CopyOnWrite<std::map<std::string, Property>> dictionary) = 0;

        /**
         * @brief Returns collection of settings from this listener
         * @return CopyOnWrite map with the settings
         */
        virtual CopyOnWrite<std::map<std::string, Property>> getDictionary() = 0;

        /**
         * @brief Virtual destructor of AbstractPropertyListener
         */
        virtual ~AbstractPropertyListener() { }

    };

    typedef std::shared_ptr<AbstractPropertyListener> AbstractPropertyListenerPtr;
}