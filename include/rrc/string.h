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
 *  @autor arssivka
 *  @date 2/24/17
 */
#pragma once


#include <ostream>
#include <cstddef>
#include <functional>
#include <memory>

namespace rrc {
    class string {
    public:
        typedef char value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* iterator;
        typedef const value_type* const_iterator;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::reverse_iterator<const_iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::function<void(value_type*)> deleter_type;

        string() noexcept;

        explicit string(const std::string& str);

        explicit string(size_type size, const value_type& val = value_type());


        template<class T>
        static string use_buffer(T* ptr, size_t size,
                                 deleter_type deleter = std::default_delete<value_type[]>()) {
            string str;
            str.m_size = sizeof(T) * size;
            str.m_data.reset((value_type*) ptr, std::move(deleter));
            return str;
        }


        template<class T>
        string(T* ptr, size_t size) {
            m_size = size * sizeof(typename std::decay<T>::type);
            m_data.reset(new value_type[m_size], std::default_delete<value_type[]>());
            std::copy(ptr, ptr + size, m_data.get());
        }

        template<class InputIterator>
        string(InputIterator first, InputIterator last)
                : string() {
            const size_t size = (size_t) std::distance(first, last);
            if (size > 0) {
                m_data.reset(new value_type[size], std::default_delete<value_type[]>());
                m_size = size;
                std::copy(first, last, m_data.get());
            }
        }

        string(const string& other) = default;

        string(string&& other) = default;

        string& operator=(const string&) = default;

        string& operator=(string&&) = default;

        value_type operator[](size_type n) const;

        size_type size() const noexcept;

        const value_type* data() const;

        const_iterator begin() const;

        const_iterator end() const;

        const_reverse_iterator rbegin() const;

        const_reverse_iterator rend() const;

        const_iterator cbegin() const;

        const_iterator cend() const;

        const_reverse_iterator crbegin() const;

        const_reverse_iterator crend() const;

        bool operator==(const string& rhs) const;

        bool operator!=(const string& rhs) const;

        bool operator==(const std::string& rhs) const;

        bool operator!=(const std::string& rhs) const;

        bool operator==(nullptr_t);

        bool operator!=(nullptr_t);

        string operator+(const string& str) const;

        friend std::ostream& operator<<(std::ostream& os, const string& buffer);

    private:
        std::shared_ptr<value_type> m_data;
        size_t m_size;
    };
}
