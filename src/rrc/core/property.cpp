/**
 * Copyright 2016 Arseniy Ivin <arssivka@yandex.ru>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @autor tekatod
 *  @date 7/15/16
 */
#include <ostream>
#include <rrc/core/property.h>
#include <mapbox/variant_io.hpp>


rrc::property::property(const std::string& value) {
    m_variant->set<std::string>(value);
}


rrc::property::property(std::string&& value) {
    m_variant->set<std::string>(std::move(value));
}


rrc::property::property(double value) {
    m_variant->set<double>(value);
}


rrc::property::property(bool value) {
    m_variant->set<bool>(value);
}


rrc::property::property(const std::vector<property>& value) {
    m_variant->set<vector>(value);
}


rrc::property::property(std::vector<property>&& value) {
    m_variant->set<vector>(std::move(value));
}


rrc::property::property(const std::unordered_map<std::string, property>& value) {
    m_variant->set<map>(value);
}


rrc::property::property(std::unordered_map<std::string, property>&& value) {
    m_variant->set<map>(std::move(value));
}


rrc::property_type rrc::property::type() const {
    switch (m_variant->which()) {
        case property_variant::which<bool>() : return property_type::BOOLEAN;
        case property_variant::which<double>() : return property_type::NUMBER;
        case property_variant::which<std::string>() : return property_type::STRING;
        case property_variant::which<vector>() : return property_type::VECTOR;
        case property_variant::which<map>() : return property_type::MAP;
        default: return property_type::UNKNOWN;
    }
}


bool rrc::property::try_get_double(double& output) const {
    if (this->is_double()) {
        output = m_variant->get_unchecked<double>();
        return true;
    }
    return false;
}


bool rrc::property::try_get_bool(bool& output) const {
    if (this->is_bool()) {
        output = m_variant->get_unchecked<bool>();
        return true;
    }
    return false;
}


bool rrc::property::try_get_string(std::string& output) const {
    if (this->is_string()) {
        output = m_variant->get_unchecked<std::string>();
        return true;
    }
    return false;
}


bool rrc::property::try_get_vector(std::vector<property>& output) const {
    if (this->is_vector()) {
        output = m_variant->get_unchecked<vector>();
        return true;
    }
    return false;
}


bool rrc::property::try_get_map(std::unordered_map<std::string, property>& output) const {
    if (this->is_map()) {
        output = m_variant->get_unchecked<map>();
        return true;
    }
    return false;
}


void rrc::property::set_bool(bool value) {
    m_variant->set<bool>(std::move(value));
}


void rrc::property::set_double(double value) {
    m_variant->set<double>(value);
}


void rrc::property::set_string(std::string&& value) {
    m_variant->set<std::string>(std::move(value));
}


void rrc::property::set_vector(std::vector<property>&& value) {
    m_variant->set<vector>(std::move(value));
}


void rrc::property::set_map(std::unordered_map<std::string, property>&& value) {
    m_variant->set<map>(std::move(value));
}


void rrc::property::set_string(const std::string& string) {
    m_variant->set<std::string>(string);
}


void rrc::property::set_vector(const std::vector<property>& value) {
    m_variant->set<vector>(value);
}


void rrc::property::set_map(const std::unordered_map<std::string, property>& value) {
    m_variant->set<map>(value);
}

bool rrc::property::is_valid() const {
    return m_variant->valid();
}


bool rrc::property::is_bool() const {
    return m_variant->is<bool>();
}


bool rrc::property::is_double() const {
    return m_variant->is<double>();
}


bool rrc::property::is_string() const {
    return m_variant->is<std::string>();
}


bool rrc::property::is_vector() const {
    return m_variant->is<vector>();
}


bool rrc::property::is_map() const {
    return m_variant->is<map>();
}


namespace rrc {
    std::ostream& operator<<(std::ostream& os, const rrc::property& property) {
        os << *property.m_variant;
        return os;
    }
}


bool rrc::property::operator==(const rrc::property& rhs) const {
    return *m_variant == *rhs.m_variant;
}


bool rrc::property::operator!=(const rrc::property& rhs) const {
    return !(rhs == *this);
}
