/**
 *  @autor tekatod
 *  @date 9/26/16
 */
#pragma once

#include "Property.h"

namespace rrc {
    class AbstractPropertyListener {
    public:

        virtual Property getProperty(std::string key) = 0;

        virtual void setDictionary(CopyOnWrite<std::map<std::string, Property>> dictionary) = 0;

        virtual CopyOnWrite<std::map<std::string, Property>> getDictionary() = 0;

        /**
         * @brief Virtual destructor of AbstractPropertyListener
         */
        virtual ~AbstractPropertyListener() { }

    };

    typedef std::shared_ptr<AbstractPropertyListener> AbstractPropertyListenerPtr;
}