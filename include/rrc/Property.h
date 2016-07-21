/**
 *  @autor tekatod
 *  @date 7/15/16
 */
#pragma once

#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "rrc/CopyOnWrite.h"
#include "mapbox/variant.hpp"

namespace rrc {
    class Property {
    public:
        typedef mapbox::util::variant<std::string, float, bool, int> SettingsType;

        template <class D>
        Property(D&& data) {
            mField = std::forward<D>(data);
        }

        template <typename T>
        T& get() const {
            switch(mField->which()) {
                case 0:
                    return getCast<T>(mField->get<std::string>());
                case 1:
                    return getCast<T>(mField->get<float>());
                case 2:
                    return getCast<T>(mField->get<bool>());
                case 3:
                    return getCast<T>(mField->get<int>());

            }
        }

        int getInt() const {
            switch(mField->which()) {
                case 0:
                    return getCast<int>(mField->get<std::string>());
                case 1:
                    return getCast<int>(mField->get<float>());
                case 2:
                    return getCast<int>(mField->get<bool>());
                case 3:
                    return getCast<int>(mField->get<int>());

            }
        }

        float getFloat() const {
            switch(mField->which()) {
                case 0:
                    return getCast<float>(mField->get<std::string>());
                case 1:
                    return getCast<float>(mField->get<float>());
                case 2:
                    return getCast<float>(mField->get<bool>());
                case 3:
                    return getCast<float>(mField->get<int>());

            }
        }

        bool getBool() const {
            switch(mField->which()) {
                case 0:
                    return getCast<bool>(mField->get<std::string>());
                case 1:
                    return getCast<bool>(mField->get<float>());
                case 2:
                    return getCast<bool>(mField->get<bool>());
                case 3:
                    return getCast<bool>(mField->get<int>());

            }
        }

        std::string getString() const {
            switch(mField->which()) {
                case 0:
                    return getCast<std::string>(mField->get<std::string>());
                case 1:
                    return getCast<std::string>(mField->get<float>());
                case 2:
                    return getCast<std::string>(mField->get<bool>());
                case 3:
                    return getCast<std::string>(mField->get<int>());

            }
        }

        template <class D>
        void set(D &&data) {
            if(std::is_same<D, bool>::value || std::is_same<D, int>::value ||
                    std::is_same<D, float>::value || std::is_same<D, std::string>::value) {
                mField->set<D>(std::forward<D>(data));
            }
            else {
                throw stderr("Unsupported type");
            };
        }

    private:
        template <typename T>
        T& getCast(T const &s) const {
            return s;
        }

//        template<>
        int getCast<int>(std::string const &s) const {
            return atoi(s);
        }

//        template<>
        float getCast<float>(std::string const &s) const {
            return std::stof(s);
        }

//        template<>
        bool getCast<bool>(std::string const &s) const {
            bool res;
            std::istringstream(s) >> std::boolalpha >> res;
            return res;
        }

        template<typename, typename D, class = typename std::enable_if<std::is_arithmetic<D>::value>::type>
        std::string getCast<std::string>(D &const n) const {
            return std::to_string(n);
        };

        template <typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type,
                typename D, class = typename std::enable_if<std::is_arithmetic<D>::value>::type>
        std::string getCast<T>(D &const n) const {
            return T(n);
        };
//        union float_bool_str {
//            std::string m_string;
//            float mfloat;
//            bool m_bool;
//            float_bool_str(std::string str) {
//                new (&m_string) std::string(str);
//            }
//            ~float_bool_str() {
//                m_string.~string();
//            }
//        };
        CopyOnWrite<SettingsType> mField;
    };
}
