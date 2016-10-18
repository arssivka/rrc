/**
 *  @autor tekatod
 *  @date 9/26/16
 */
#pragma once


#include "AbstractPropertyListener.h"
#include <map>

namespace rrc{
    /**
     * @brief Class inherited form the AbstractMessageListener. The most usual listener. Nothing really special is going here.
     */
    class PropertyListener : public AbstractPropertyListener {
    public:

        /**
         * @brief Returns property with the specified name
         * @param propertyName Name of the required property
         * @return Property Required property.
         */
        virtual Property getProperty(const std::string& propertyName) override;

        /**
         * @brief Sets the collection of settings to this listener
         * @param dictionary PropertyDictionary with the required settings
         */
        virtual void setDictionary(PropertyDictionary dictionary) override;

        /**
          * @brief Returns collection of settings from this listener
          * @return PropertDictionary with the settings
          */
        virtual PropertyDictionary getDictionary() override;

        /**
         * @brief Checks if there is such Property with the specified name
         * @param propertyName Name of the needed property
         * @return True if such Property exists, otherwise false.
         */
        virtual bool isContainsName(const std::string &propertyName) override;

    private:
        PropertyDictionary mPropertyDictionary;
    };

    typedef std::shared_ptr<PropertyListener> PropertyListenerPtr;
}
