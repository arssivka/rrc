/**
 *  @autor tekatod
 *  @date 9/26/16
 */
#pragma once

#include "Property.h"

namespace rrc {
    class AbstractPropertyListener {
    public:

        virtual void setProperty(Property property) = 0;

        virtual Property getProperty() = 0;

        /**
         * @brief Virtual destructor of AbstractPropertyListener
         */
        virtual ~AbstractPropertyListener() { }

    };

    typedef std::shared_ptr<AbstractPropertyListener> AbstractPropertyListenerPtr;
}