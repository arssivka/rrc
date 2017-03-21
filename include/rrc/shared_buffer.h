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
#include "copy_on_write.h"
#include "array_deleter.h"

namespace rrc {
    class shared_buffer {
    public:
        typedef char value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef const value_type* iterator;
        typedef const value_type* const_iterator;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::reverse_iterator<const_iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef size_t site_type;

        shared_buffer();

        explicit shared_buffer(const std::string& str);

        explicit shared_buffer(size_type size, const value_type& val = value_type());

        template <class T>
        shared_buffer(const T* ptr, size_t size) {
            m_size = size * sizeof(typename std::decay<T>::type);
            m_data.reset(new value_type[m_size], array_deleter<value_type>());
            std::copy(ptr, ptr + size, m_data.get());
        }

        template<class InputIterator>
        shared_buffer(InputIterator first, InputIterator last) {
            const size_t size = (size_t) std::distance(first, last);
            m_data.reset(new value_type[size], array_deleter<value_type>());
            m_size = size;
            std::copy(first, last, m_data.get());
        }

        shared_buffer(const shared_buffer& other) = default;

        shared_buffer(shared_buffer&& other) = default;

        shared_buffer& operator=(const shared_buffer&) = default;

        shared_buffer& operator=(shared_buffer&&) = default;

        reference operator[](size_type n);

        const_reference operator[](size_type n) const;

        void fill(const value_type& value);

        size_type size() const noexcept;

        value_type* data();

        const value_type* data() const;

        const_iterator begin() const;

        const_iterator end() const;

        const_reverse_iterator rbegin() const;

        const_reverse_iterator rend() const;

        const_iterator cbegin() const;

        const_iterator cend() const;

        const_reverse_iterator crbegin() const;

        const_reverse_iterator crend() const;

        bool operator==(const shared_buffer& rhs) const;

        bool operator!=(const shared_buffer& rhs) const;

        bool operator==(const std::string& rhs) const;

        bool operator!=(const std::string& rhs) const;

        bool operator==(nullptr_t);

        bool operator!=(nullptr_t);

        friend std::ostream& operator<<(std::ostream& os, const shared_buffer& buffer);

    private:
        void ensure_initialized() const;

        void ensure_unique();


    private:
        mutable std::shared_ptr<value_type> m_data;
        mutable size_t m_size;
    };
}
