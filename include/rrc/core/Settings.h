/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once

#include <string>
#include <unordered_map>
#include <forward_list>
#include <set>
#include "AbstractPropertyListener.h"

namespace rrc {
    class Settings {
    public:

        Settings();

        template <class T>
        void addOrUpdateProperty(const std::string &key, T&& property) {
            auto container = mListenerContainers.find(key);
            if(container != mListenerContainers.end()) {
                container->second.updateProperty(Property(std::forward<T>(property)));
            } else {
                mListenerContainers.insert({key, PropertyListenerContainer(Property(std::forward<T>(property)))});
            }
        }

        void removeProperty(const std::string &key);

        void addListener(const std::string &key, AbstractPropertyListenerPtr listener);

        void removeListener(const std::string &key, AbstractPropertyListenerPtr listener);

        bool empty() const;

        bool contains(const std::string &key) const;

        bool hasListeners(const std::string &key) const;

        std::set<std::string> getKeys() const;


    private:

        struct PropertyListenerContainer {

            PropertyListenerContainer(Property property);

            void addListener(AbstractPropertyListenerPtr listener);

            void removeListener(AbstractPropertyListenerPtr listener);

            void updateProperty(Property property);

            bool hasListeners() const;

            std::forward_list<AbstractPropertyListenerPtr> mListenerList;

            Property mProperty;
        };
        std::unordered_map<std::string, PropertyListenerContainer> mListenerContainers;
    };
}


