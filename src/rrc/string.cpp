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
 *  @date 3/16/17
 */

#include <rrc/string.h>
#include <algorithm>


namespace rrc {
    rrc::string::string() noexcept
            : m_data(nullptr),
              m_size(0) {}


    rrc::string::string(const std::string& str)
            : string(str.begin(), str.end()) {}


    rrc::string::string(rrc::string::size_type size,
                        const rrc::string::value_type& val)
            : string() {
        m_size = size;
        if (m_size > 0) {
            m_data.reset(new value_type[size],
                         std::default_delete<value_type[]>());
            iterator beg = m_data.get();
            iterator end = m_data.get() + m_size;
            std::fill(beg, end, val);
        }
    }


    rrc::string::value_type rrc::string::operator[](rrc::string::size_type n) const {
        const value_type* data = m_data.get();
        return data[n];
    }


    rrc::string::size_type rrc::string::size() const noexcept {
        return m_size;
    }


    const rrc::string::value_type* rrc::string::data() const noexcept {
        return m_data.get();
    }


    rrc::string::const_iterator rrc::string::begin() const noexcept {
        return const_iterator(m_data.get());
    }


    rrc::string::const_iterator rrc::string::end() const noexcept {
        return const_iterator(m_data.get() + this->size());
    }


    rrc::string::const_reverse_iterator rrc::string::rbegin() const noexcept {
        return const_reverse_iterator(end());
    }


    rrc::string::const_reverse_iterator rrc::string::rend() const noexcept {
        return const_reverse_iterator(begin());
    }


    rrc::string::const_iterator rrc::string::cbegin() const noexcept {
        return const_iterator(m_data.get());
    }


    rrc::string::const_iterator rrc::string::cend() const noexcept {
        return const_iterator(m_data.get() + this->size());
    }


    rrc::string::const_reverse_iterator rrc::string::crbegin() const noexcept {
        return const_reverse_iterator(end());
    }


    rrc::string::const_reverse_iterator rrc::string::crend() const noexcept {
        return const_reverse_iterator(begin());
    }


    bool rrc::string::operator==(const rrc::string& rhs) const noexcept {
        if (m_data == nullptr || rhs.m_data == nullptr) {
            return m_data.get() == rhs.m_data.get();
        }
        return m_size == rhs.m_size && std::equal(this->cbegin(), this->cend(), rhs.cbegin());
    }


    bool rrc::string::operator!=(const rrc::string& rhs) const noexcept {
        return !(*this == rhs);
    }


    bool rrc::string::operator==(const std::string& rhs) const noexcept {
        return m_size == rhs.size() &&
                std::equal(m_data.get(), m_data.get() + m_size, rhs.begin());
    }


    bool rrc::string::operator!=(const std::string& rhs) const noexcept {
        return !(*this == rhs);
    }


    std::ostream& operator<<(std::ostream& os, const rrc::string& buffer) {
        for (auto&& symb : buffer) {
            if (symb == '\0') break;
            os << symb;
        }
        return os;
    }


    bool string::operator==(nullptr_t) noexcept {
        return m_data == nullptr;
    }


    bool string::operator!=(nullptr_t) noexcept {
        return !(*this == nullptr);
    }

    string string::operator+(const string& str) const {
        string res;
        const_iterator beg;
        const_iterator end;
        iterator out;

        res.m_size = m_size + str.m_size;
        res.m_data.reset(new value_type[res.m_size]);

        beg = m_data.get();
        end = m_data.get() + m_size;
        out = res.m_data.get();
        std::copy(beg, end, out);
        beg = str.m_data.get();
        end = str.m_data.get() + str.m_size;
        out = res.m_data.get() + m_size;
        std::copy(beg, end, out);

        return res;
    }

    bool string::is(const string& other) const noexcept {
        return m_data.get() == other.m_data.get();
    }
}
