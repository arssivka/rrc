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

        explicit buffer(size_type size, const value_type& val = value_type())
                : m_data(size, val) {
        }

        template<class InputIterator>
        buffer(InputIterator first, InputIterator last)
                : m_data(make_cow<value_type>(first, last)) {}

        buffer(const buffer& other) = default;

        buffer(buffer&& other) = default;

        reference operator[](size_type n) {
            return m_data->at(n);
        }

        const_reference operator[](size_type n) const {
            return m_data->at(n);
        }

        void fill(const value_type& value) { std::fill_n(begin(), size(), value); }

        size_type size() const noexcept { return m_data->size(); }

        value_type* data() { return m_data->data(); }

        const value_type* data() const { return m_data->data(); }

        const_iterator begin() const { return const_iterator(m_data->data()); }

        const_iterator end() const { return const_iterator(m_data->data() + this->size()); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        const_iterator cbegin() const { return const_iterator(m_data->data()); }

        const_iterator cend() const { return const_iterator(m_data->data() + this->size()); }

        const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }

        const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    private:
        copy_on_write<std::vector<value_type>> m_data;

    };
}
