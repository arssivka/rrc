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
#include "copy_on_write.h"

namespace rrc {
    template<class T>
    class buffer {
    public:
        typedef T value_type;
        typedef value_type& reference;
        typedef const reference const_reference;
        typedef const value_type* iterator;
        typedef const value_type* const_iterator;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::reverse_iterator<const_iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef size_t site_type;

        explicit buffer(size_type size, const value_type& val = value_type()) {
            m_data = copy_on_write<value_type>(new value_type[size]);
            m_size = size;
            this->fill(val);
        }

        template<class InputIterator>
        buffer(InputIterator first, InputIterator last) {
            size_t size = (size_t) std::distance(first, last);
            m_data = copy_on_write<value_type>(new value_type[size]);
            m_size = size;
            std::copy(first, last, m_data.get());
        }

        buffer(const buffer& other) = default;

        buffer(buffer&& other) = default;

        reference operator[](size_type n) {
            return (*m_data)[n];
        }

        const_reference operator[](size_type n) const {
            return (*m_data)[n];
        }

        void fill(const value_type& value) { std::fill_n(begin(), size(), value); }

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

    private:
        copy_on_write<value_type> m_data;
        size_t m_size;
    };
}
