/**
 *  @autor tekatod
 *  @date 9/26/16
 */
#pragma once

#include "AbstractPropertyListener.h"
#include <map>

namespace rrc{
    /**
     * @brief Class inherited form the AbstractMessageListener. Themost usual listener. Nothing really special is going here.
     */
    class PropertyListener : public AbstractPropertyListener {
    public:

        /**
         * @brief Returns property with the specified name
         * @param key Name of the needed property
         * @return Property
         */
        virtual Property getProperty(std::string key) override;

        /**
        * @brief Sets the collection of settings to this listener
        * @param dictionary CopyOnWrite map with the needed settings
        */
        virtual void setDictionary(CopyOnWrite<std::map<std::string, Property>> dictionary) override;

        /**
        * @brief Returns collection of settings from this listener
        * @return CopyOnWrite map with the settings
        */
        virtual CopyOnWrite<std::map<std::string, Property>> getDictionary() override;

    private:
        CopyOnWrite<std::map<std::string, Property>> mPropertyDictionary;
    };

    typedef std::shared_ptr<PropertyListener> PropertyListenerPtr;
}