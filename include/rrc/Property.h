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

        Property(const char* str) {
            mField->set<std::string>(str);
        }

        Property(std::string str) {
            mField->set<std::string>(str);
        }

        Property(Property& p) = default;
        Property(const Property& p) = default;
        Property(Property&& p) = default;

        template <class D>
        Property(D&& data) {
            mField->set<D>(std::forward<D>(data));
        }

        Property() {

        }

        template <typename T>
        T get() const {
        }

        int getInt();

        float getFloat();

        bool getBool();

        std::string getString();

        void set(const char* str) {
            mField->set<std::string>(str);
        }

        void set(std::string str) {
            mField->set<std::string>(str);
        }

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