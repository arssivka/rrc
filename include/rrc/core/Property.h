/**
 *  @autor tekatod
 *  @date 7/15/16
 */
#pragma once

#include <string>
#include <stdlib.h>
#include <sstream>
#include "CopyOnWrite.h"
#include "mapbox/variant.hpp"

namespace rrc {
    class Property {
    public:
        typedef mapbox::util::variant<std::string, float, bool, int> SettingsType;

        /**
         * @brief Property constructor from const char*
         * @param str String to store int property
         */
        Property(const char* str) {
            mField->set<std::string>(str);
        }

        /**
         * @brief Property constructor from std::string
         * @param str String to store int property
         */
        Property(std::string str) {
            mField->set<std::string>(str);
        }

        /**
         * @brief Copy constructor of property
         * @param other Other property instance to copy from
         */
        Property(Property& other) = default;

        /**
         * @brief Copy constructor of property
         * @param other Other const property instance to copy from
         */
        Property(const Property& other) = default;

        /**
         * @brief Move constructor of property
         * @param other Other property instance to move from
         */
        Property(Property&& other) = default;

        /**
         * @brief Constructor of property from int, float or bool
         * @param data Int, float or bool to store
         */
        template <class D>
        Property(D&& data) {
            mField->set<D>(std::forward<D>(data));
        }

        /**
         * @brief Default property constructor
         */
        Property() { }

        /**
         * @brief Default = Operator of property
         * @param other Const reference to Property instance
         * @return Property&
         */
        Property& operator= (const Property& other) = default;

        /**
         * @brief Default = Operator of property
         * @param other Rvalue reference to Property instance
         * @return Property&
         */
        Property& operator= (Property&& other) = default;

        /**
         * @brief Universal method to get content of property. Can parametrizied by string, bool, int or float
         * @return Content of property of desired type
         */
        template <typename T>
        T get() const;

        /**
         * @brief Returns content of property of int type
         * @return Content of int type
         */
        int getInt();

        /**
         * @brief Returns content of property of float type
         * @return Content of float type
         */
        float getFloat();

        /**
         * @brief Returns content of property of bool type
         * @return Content of bool type
         */
        bool getBool();

        /**
         * @brief Returns content of property of std::string type
         * @return Content of std::string type
         */
        std::string getString();

        /**
         * @brief Sets content of property from const char*
         * @param str String to set
         */
        void set(const char* str) {
            mField->set<std::string>(str);
        }

        /**
         * @brief Sets content of property from std::string
         * @param str String to set
         */
        void set(std::string str) {
            mField->set<std::string>(str);
        }

        /**
         * @brief Sets content of property from int, bool or float
         * @param str Data to set
         */
        template <typename D>
        void set(D &&data) {
            if(std::is_same<D, bool>::value || std::is_same<D, int>::value ||
               std::is_same<D, float>::value || std::is_same<D, std::string>::value) {
                mField->set<D>(std::forward<D>(data));
            }
            else {
                std::cerr << "Unsupported type\n";
            };
        }

    private:
        CopyOnWrite<SettingsType> mField;
    };
}