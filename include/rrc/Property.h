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

    template<>
    int Property::get<int>() const {
        int id = mField->which();
        switch(id){
            case 0:
                return std::stoi(mField->get<std::string>());
            case 1:
                return (int)mField->get<float>();
            case 2:
                return (int)mField->get<bool>();
            case 3:
                return mField->get<int>();
        }

    }

    template<>
    float Property::get<float>() const {
        int id = mField->which();
        switch(id){
            case 0:
                return std::stof(mField->get<std::string>());
            case 1:
                return mField->get<float>();
            case 2:
                return (float)mField->get<bool>();
            case 3:
                return (float)mField->get<int>();
        }
    }

    template<>
    bool Property::get<bool>() const {
        int id = mField->which();
        switch(id){
            case 0:
                bool res;
                std::istringstream(mField->get<std::string>()) >> std::boolalpha >> res;
                return res;
            case 1:
                return (bool)mField->get<float>();
            case 2:
                return mField->get<bool>();
            case 3:
                return (bool)mField->get<int>();
        }
    }

    template<>
    std::string Property::get<std::string>() const {
        int id = mField->which();
        switch(id){
            case 0:
                return mField->get<std::string>();
            case 1:
                return std::to_string(mField->get<float>());
            case 2:
                return std::to_string(mField->get<bool>());
            case 3:
                return std::to_string(mField->get<int>());
        }
    }

    int Property::getInt() {
        this->get<int>();
    }

    float Property::getFloat() {
        this->get<float>();
    }
    bool Property::getBool() {
        this->get<bool>();
    }

    std::string Property::getString() {
        this->get<std::string>();
    }
}

