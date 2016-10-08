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
    class SettingsHolder {
    public:

        /**
         * @brief Method for adding property to settings collection(it wiil create collection if there is no such one). Also it can update value of existing property.
         * @param dictionaryName Name of the collection in which you need to store or update your property.
         * @param propertyName Name of the property that you need to update or create.
         * @param property It is a needed value of type int, float, bool or std:string or Property instance.
         */
        template<class T>
        void addOrUpdateProperty(const std::string& dictionaryName, const std::string& propertyName, T&& property) {
            auto dictionary = mDictionaries.find(dictionaryName);
            if(dictionary != mDictionaries.end()) {
                dictionary->second.addOrUpdateProperty(propertyName, std::forward<T>(property));
            }
            else {
                mDictionaries.insert({dictionaryName, PropertyContainer(propertyName, std::forward<T>(property))});
            }
        }

        /**
         * @brief Checks if there is any settings collection in SettingsHolder.
         * @return True if there is some, otherwise false.
         */
        bool isEmpty() const;

        /**
         * @brief Checks if dictionary with the specified name contains some properties.
         * @param dictionaryName Name of the dictionary.
         * @return False if dictionary contains something, otherwise true.
         */
        bool isDictionaryEmpty(const std::string& dictionaryName) const;

        /**
           * @brief Checks if dictionary with the specified has listeners.
           * @param dictionaryName Name of the dictionary.
           * @return True if dictionary has listeners, otherwise false.
           */
        bool isDictionaryHasListeners(const std::string& dictionaryName) const;

        /**
         * @brief Checks if dictionary with the specified name contains property with the specified name.
         * @param dictionaryName Name of the dictionary to search property in it.
         * @param propertyName Name of the property to check.
         * @return True if there's such property in the dictionary, otherwise false.
         */
        bool isDictionaryContainsProperty(const std::string& dictionaryName, const std::string& propertyName) const;

        /**
         * @brief Returns names of the settings collections in SettingsHolder.
         * @return Vector with the names of collections. Empty vector if there are no collections.
         */
        std::vector<std::string> getNames() const;

        /**
         * @brief Returns names of the properties that stored in the dictionary with the specified name.
         * @param dictionaryName Name of the needed dictionary.
         * @return Vector with the names of properties. Empty vector if there are no properties or collections with such name.
         */
        std::vector<std::string> getDictionaryNames(const std::string& dictionaryName) const;

        /**
         * @brief Checks if there settings collection with such name.
         * @param dictionaryName Name of the dictionary to check.
         * @return True if exists, otherwise false.
         */
        bool hasDictionary(const std::string& dictionaryName) const;

        /**
         * @brief Removes property with the specified name from the collection with the specified name.
         * @param dictionaryName Name of the dictionary to remove property from it.
         * @param propertyName Name of the property to remove.
         */
        void removeProperty(const std::string& dictionaryName, const std::string& propertyName);

        /**
         * @brief Adds listener for the dictionary with the specified name.
         * @param dictionaryName Name of the dictionary for adding listener to it.
         * @param listener Pointer to listener to add.
         */
        void addListener(const std::string& dictionaryName, AbstractPropertyListenerPtr listener);

        /**
         * @brief Removes listener from the dictionary with the specified name.
         * @param dictionaryName Name of the dictionary for removing listener from it.
         * @param listener Pointer to listener to remove.
         */
        void removeListener(const std::string& dictionaryName, AbstractPropertyListenerPtr listener);

        /**
         * @brief Removes dictionary with the specified name from the SettingsHolder.
         * @param dictionaryName Name of the dictionary to remove.
         */
        void removeDictionary(const std::string& dictionaryName);

    private:
        struct PropertyContainer {

            PropertyContainer() = default;

            template <class T>
            PropertyContainer(const std::string& propertyName, T&& property) {
                this->addOrUpdateProperty(propertyName, std::forward<T>(property));
            }

            template<class T>
            void addOrUpdateProperty(const std::string& propertyName, T&& property) {
                mPropertyDictionary.addOrUpdateProperty(propertyName, std::forward<T>(property));
                for (auto&& listener : mListeners) {
                    listener->setDictionary(PropertyDictionary(mPropertyDictionary));
                }
            }

            void removeProperty(const std::string& propertyName);

            void addListener(AbstractPropertyListenerPtr listener);

            void removeListener(AbstractPropertyListenerPtr listener);

            bool isEmpty() const;

            bool isContains(const std::string& propertyName) const;

            bool hasListeners() const;

            std::vector<std::string> getNames() const;

            PropertyDictionary mPropertyDictionary;
            std::forward_list<AbstractPropertyListenerPtr> mListeners;
        };
        std::map<std::string, PropertyContainer> mDictionaries;
    };
}


