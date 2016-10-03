/**
 *  @autor tekatod
 *  @date 9/26/16
 */
#pragma once

#include "AbstractPropertyListener.h"
#include <map>

namespace rrc{
    class PropertyListener : public AbstractPropertyListener {
    public:

        virtual Property getProperty(std::string key) override;

        virtual void setDictionary(CopyOnWrite<std::map<std::string, Property>> dictionary) override;

        virtual CopyOnWrite<std::map<std::string, Property>> getDictionary() override;

    private:
        CopyOnWrite<std::map<std::string, Property>> mPropertyDictionary;
    };

    typedef std::shared_ptr<PropertyListener> PropertyListenerPtr;
}