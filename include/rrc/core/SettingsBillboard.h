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
    /**
     * @brief Class that holds settings collections aka. PropertyDictionary and grants access to some properties via listeners.
     */
    class SettingsBillboard {
    public:

        /**
         * @brief Method for adding property to settings collection(it wiil create collection if there is no such one). Also it can update value of existing property.
         * @param dictionaryKey Name of the collection in which you need to store or update your property.
         * @param propertyKey Name of the property that you need to update or create.
         * @param property It is a needed value of type int, float, bool or std:string or Property instance.
         */
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

        /**
         * @brief Checks if there is any settings collection in SettingsBillboard.
         * @return True if there is some, otherwise false.
         */
        bool empty() const;

        /**
         * @brief Checks if dictionary with the specified name contains some properties.
         * @param dictionaryKey Name of the dictionary.
         * @return False if dictionary contains something, otherwise true.
         */
        bool isDictionaryEmpty(const std::string& dictionaryKey) const;

        /**
           * @brief Checks if dictionary with the specified has listeners.
           * @param dictionaryKey Name of the dictionary.
           * @return True if dictionary has listeners, otherwise false.
           */
        bool isDictionaryHasListeners(const std::string& dictionaryKey) const;

        /**
         * @brief Checks if dictionary with the specified name contains property with the specified name.
         * @param dictionaryKey Name of the dictionary to search property in it.
         * @param propertyKey Name of the property to check.
         * @return True if there's such property in the dictionary, otherwise false.
         */
        bool isDictionaryContainsProperty(const std::string& dictionaryKey, const std::string& propertyKey) const;

        /**
         * @brief Returns names of the settings collections in SettingsBillboard.
         * @return Vector with the names of collections. Empty vector if there are no collections.
         */
        std::vector<std::string> getKeys() const;

        /**
         * @brief Returns names of the properties that stored in the dictionary with the specified name.
         * @param dictionaryKey Name of the needed dictionary.
         * @return Vector with the names of properties. Empty vector if there are no properties or collections with such name.
         */
        std::vector<std::string> getDictionaryKeys(const std::string& dictionaryKey) const;

        /**
         * @brief Checks if there settings collection with such name.
         * @param dictionaryKey Key of the dictionary to check.
         * @return True if exists, otherwise false.
         */
        bool hasDictionary(const std::string& dictionaryKey) const;

        /**
         * @brief Removes property with the specified name from the collection with the specified name.
         * @param dictionaryKey Name of the dictionary to remove property from it.
         * @param propertyKey Name of the property to remove.
         */
        void removeProperty(const std::string& dictionaryKey, const std::string& propertyKey);

        /**
         * @brief Adds listener for the dictionary with the specified name.
         * @param dictionaryKey Name of the dictionary for adding listener to it.
         * @param listener Pointer to listener to add.
         */
        void addListener(const std::string& dictionaryKey, AbstractPropertyListenerPtr listener);

        /**
         * @brief Removes listener from the dictionary with the specified name.
         * @param dictionaryKey Name of the dictionary for removing listener from it.
         * @param listener Pointer to listener to remove.
         */
        void removeListener(const std::string& dictionaryKey, AbstractPropertyListenerPtr listener);

        /**
         * @brief Removes dictionary with the specified name from the SettingsBillboard.
         * @param dictionaryKey Name of the dictionary to remove.
         */
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


