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
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @autor arssivka
 *  @date 4/13/17
 */

#pragma once


#include <boost/lexical_cast.hpp>
#include <string>
#include <unordered_map>

namespace rrc {
    class preferences {
    public:
        template <class T>
        bool set(const std::string& name, T&& value) {
            try {
                std::string str_value = boost::lexical_cast<std::string>(value);
                m_hash.emplace(name, std::move(str_value));
                return true;
            } catch (const boost::bad_lexical_cast& e) {
                return false;
            }
        }

        template <class T>
        bool get(const std::string& name, T& value) const noexcept(std::is_nothrow_copy_assignable<T>::value) {
            auto it = m_hash.find(name);
            if (it == m_hash.end()) return false;
            try {
                value = boost::lexical_cast<T>(it->second);
                return true;
            } catch (const boost::bad_lexical_cast& e) {
                return false;
            }
        }


    private:
        std::unordered_map<std::string, std::string> m_hash;

    };
}


