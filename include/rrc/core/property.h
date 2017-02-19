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
#pragma once


#include <ostream>
#include <unordered_map>
#include <vector>
#include "mapbox/variant.hpp"
#include "mapbox/recursive_wrapper.hpp"
#include "copy_on_write.h"


namespace rrc {
    enum class property_type : int {
        NIL,
        BOOLEAN,
        NUMBER,
        STRING,
        VECTOR,
        MAP,
        UNKNOWN
    };

    /**
     * @brief Property is a class for holding and modifying the setting of the node. It can hold float, bool, int or string.
     */
    class property {
    public:
        property(double value);

        property(bool value);

        property(const std::string& value);

        property(std::string&& value);

        property(const std::vector<property>& vector);

        property(std::vector<property>&& vector);

        property(const std::unordered_map<std::string, property>& table);

        property(std::unordered_map<std::string, property>&& table);

        /**
         * @brief Copy constructor of property
         * @param other Other const property instance to copy from
         */
        property(const property& other) = default;

        /**
         * @brief Move constructor of property
         * @param other Other property instance to move from
         */
        property(property&& other) = default;

        /**
         * @brief Default property constructor
         */
        property() = default;

        /**
         * @brief Default = Operator of property
         * @param other Const reference to Property instance
         * @return Property&
         */
        property& operator=(const property& other) = default;

        /**
         * @brief Default = Operator of property
         * @param other Rvalue reference to Property instance
         * @return Property&
         */
        property& operator=(property&& other) = default;

        property_type type() const;

        bool try_get_double(double& output) const;

        bool try_get_bool(bool& output) const;

        bool try_get_string(std::string& output) const;

        bool try_get_vector(std::vector<property>& output) const;

        bool try_get_map(std::unordered_map<std::string, property>& output) const;

        template <class T>
        void set(T&& value) {
            m_variant->set<T>(std::forward<T>(value));
        }

        void set_bool(bool value);

        void set_double(double value);

        void set_string(std::string&& value);

        void set_string(const std::string& string);

        void set_vector(std::vector<property>&& vector);

        void set_map(std::unordered_map<std::string, property>&& map);

        void set_vector(const std::vector<property>& vector);

        void set_map(const std::unordered_map<std::string, property>& map);

        bool is_valid() const;

        bool is_bool() const;

        bool is_double() const;

        bool is_string() const;

        bool is_vector() const;

        bool is_map() const;

        bool operator==(const property& rhs) const;

        bool operator!=(const property& rhs) const;

        friend std::ostream& operator<<(std::ostream& os, const rrc::property& property);

    private:
        template <class T> using recursive_wrapper = mapbox::util::recursive_wrapper<T>;
        template <class... Ts> using variant = mapbox::util::variant<Ts...>;
        typedef recursive_wrapper<std::vector<property>> vector;
        typedef recursive_wrapper<std::unordered_map<std::string, property>> map;
        typedef variant<double, bool, std::string, vector, map> property_variant;
        copy_on_write<property_variant> m_variant;

    };
}