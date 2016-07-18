/**
 *  @autor tekatod
 *  @date 7/15/16
 */
#pragma once

#include <string>
#include "rrc/CopyOnWrite.h"
#include "mapbox/variant.hpp"

namespace rrc {
    typename <class T>
    class SettingsField {
    public:
        typedef mapbox::util::variant<std::string, float, bool, int> SettingsType;

        template <class D>
        SettingsField(D&& data) {
            m_field = std::forward<D>(data);
        }

        const T& getSetting() {
            return m_field->get();
        }

        template <class D>
        void setSetting(D&& data) {
            m_field = std::forward<D>(data);
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
    CopyOnWrite<SettingsType> m_field;
    };
}
