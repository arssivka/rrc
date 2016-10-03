/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once

#include <string>
#include <map>
#include <forward_list>
#include <set>
#include "AbstractPropertyListener.h"
#include "CopyOnWrite.h"

namespace rrc {
    class SettingsBillboard {
    public:

        template<class T>
        void addOrUpdateProperty(const std::string &dictionaryKey, const std::string &propertyKey, T&& property) {
            auto dictionary = mDictionaries.find(dictionaryKey);
            if(dictionary != mDictionaries.end()) {
                dictionary->second.addOrUpdateProperty(propertyKey, std::forward<Property>(property));
            }
            else {
                PropertyDictionary propertyDictionary;
                propertyDictionary.addOrUpdateProperty(propertyKey, std::forward<Property>(property));
                mDictionaries.insert({dictionaryKey, propertyDictionary});
            }
        }
    private:
        struct PropertyDictionary {
            PropertyDictionary();

            template<class T>
            void addOrUpdateProperty(const std::string &key, T &&property) {
                auto container = mPropertyDictionary->find(key);
                if (container != mPropertyDictionary->end()) {
                    container->second = std::forward<T>(property);
                } else {
                    mPropertyDictionary->insert({key, Property(std::forward<T>(property))});
                }
                for (auto &&listener : mListeners) {
                    listener->setDictionary(mPropertyDictionary);
                }
            }

            void removeProperty(const std::string &key);

            void addListener(AbstractPropertyListenerPtr listener);

            void removeListener(AbstractPropertyListenerPtr listener);

            bool empty() const;

            bool contains(const std::string &key) const;

            bool hasListeners() const;

            std::set<std::string> getKeys() const;

            CopyOnWrite<std::map<std::string, Property>> mPropertyDictionary;
            std::forward_list<AbstractPropertyListenerPtr> mListeners;
        };
        std::map<std::string, PropertyDictionary> mDictionaries;
    };
}


