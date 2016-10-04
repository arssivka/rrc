/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once

#include <string>
#include <map>
#include <forward_list>
#include <set>
#include <vector>
#include "AbstractPropertyListener.h"
#include "CopyOnWrite.h"

namespace rrc {
    class SettingsBillboard {
    public:

        template<class T>
        void addOrUpdateProperty(const std::string& dictionaryKey, const std::string& propertyKey, T&& property) {
            auto dictionary = mDictionaries.find(dictionaryKey);
            if(dictionary != mDictionaries.end()) {
                dictionary->second.addOrUpdateProperty(propertyKey, std::forward<T>(property));
            }
            else {
                mDictionaries.insert({dictionaryKey, PropertyDictionary(propertyKey, std::forward<T>(property))});
            }
        }

        bool empty() const;

        bool isDictionaryEmpty(const std::string& dictionaryKey) const;

        bool isDictionaryHasListeners(const std::string& dictionaryKey) const;

        bool isDictionaryContainsProperty(const std::string& dictionaryKey, const std::string& propertyKey) const;

        std::vector<std::string> getKeys() const;

        std::vector<std::string> getDictionaryKeys(const std::string& dictionaryKey) const;

        bool hasDictionary(const std::string& dictionaryKey) const;

        void removeProperty(const std::string& dictionaryKey, const std::string& propertyKey);

        void addListener(const std::string& dictionaryKey, AbstractPropertyListenerPtr listener);

        void removeListener(const std::string& dictionaryKey, AbstractPropertyListenerPtr listener);

        void removeDictionary(const std::string& dictionaryKey);

    private:
        struct PropertyDictionary {

            PropertyDictionary() = default;

            template <class T>
            PropertyDictionary(const std::string& key, T&& property) {
                this->addOrUpdateProperty(key, std::forward<T>(property));
            }

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

            std::vector<std::string> getKeys() const;

            CopyOnWrite<std::map<std::string, Property>> mPropertyDictionary;
            std::forward_list<AbstractPropertyListenerPtr> mListeners;
        };
        std::map<std::string, PropertyDictionary> mDictionaries;
    };
}


