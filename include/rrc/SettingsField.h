/**
 *  @autor tekatod
 *  @date 7/15/16
 */
#pragma once

#include <string>

namespace rrc {
    class SettingsField {
    private:
        union float_bool_str {
            std::string m_string;
            float mfloat;
            bool m_bool;
            float_bool_str(std::string str) {
                new (&m_string) std::string(str);
            }
            ~float_bool_str() {
                m_string.~string();
            }
        };
        float_bool_str m_settings;
    };
}
