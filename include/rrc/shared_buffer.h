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


#include <vector>
#include <algorithm>
#include <ostream>
#include "copy_on_write.h"

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

        shared_buffer() : m_data(), m_size(0) { }

        explicit shared_buffer(const std::string& str) {
            m_data = copy_on_write<value_type>(new value_type[str.size()]);
            std::copy(str.cbegin(), str.cend(), m_data.get());
            m_size = str.size();
        }

        explicit shared_buffer(size_type size, const value_type& val = value_type()) {
            m_data = copy_on_write<value_type>(new value_type[size]);
            m_size = size;
            this->fill(val);
        }

        template<class InputIterator>
        shared_buffer(InputIterator first, InputIterator last) {
            size_t size = (size_t) std::distance(first, last);
            m_data = copy_on_write<value_type>(new value_type[size]);
            m_size = size;
            std::copy(first, last, m_data.get());
        }

        shared_buffer(const shared_buffer& other) = default;

        shared_buffer(shared_buffer&& other) = default;

        shared_buffer& operator=(const shared_buffer&) = default;

        shared_buffer& operator=(shared_buffer&&) = default;

        reference operator[](size_type n) {
            value_type* data = m_data.get();
            return data[n];
        }

        const_reference operator[](size_type n) const {
            const value_type* data = m_data.get();
            return data[n];
        }

        void fill(const value_type& value) { std::fill_n(m_data.get(), size(), value); }

        size_type size() const noexcept { return m_size; }

        value_type* data() { return m_data.get(); }

        const value_type* data() const { return m_data.get(); }

        const_iterator begin() const { return const_iterator(m_data.get()); }

        const_iterator end() const { return const_iterator(m_data.get() + this->size()); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        const_iterator cbegin() const { return const_iterator(m_data.get()); }

        const_iterator cend() const { return const_iterator(m_data.get() + this->size()); }

        const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }

        const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

        bool operator==(const shared_buffer& rhs) const {
            return m_size == rhs.m_size && std::equal(this->cbegin(), this->cend(), rhs.cbegin());
        }

        bool operator!=(const shared_buffer& rhs) const {
            return !(*this == rhs);
        }

        bool operator==(const std::string& rhs) const {
            return m_size == rhs.size() && rhs.compare(m_data.get()) == 0;
        }

        bool operator!=(const std::string& rhs) const {
            return !(*this == rhs);
        }

        friend std::ostream& operator<<(std::ostream& os, const shared_buffer& buffer) {
            os << buffer.data();
            return os;
        }


    private:
        copy_on_write<value_type> m_data;
        size_t m_size;
    };
}
