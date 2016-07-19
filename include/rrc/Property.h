/**
 *  @autor tekatod
 *  @date 7/15/16
 */
#pragma once

#include <string>
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

        template <class T>
        T& get() const {
            return mField->get().get();
        }

        template <class D>
        void set(D &&data) {
            mField = std::forward<D>(data);
        }

    private:
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
        SettingsType test;
    };
}
