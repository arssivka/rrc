/**
 *  @autor tekatod
 *  @date 9/26/16
 */
#pragma once

#include "AbstractPropertyListener.h"

namespace rrc{
    class PropertyListener : public AbstractPropertyListener {
    public:

        virtual void setProperty(Property property) override;

        virtual Property getProperty() override;

    private:
        Property mProperty;
    };

    typedef std::shared_ptr<PropertyListener> PropertyListenerPtr;
}