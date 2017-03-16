/**
 *  @autor arssivka
 *  @date 3/16/17
 */

#include <rrc/shared_buffer.h>


rrc::shared_buffer::shared_buffer()
        : m_data(), m_size(0) { }


rrc::shared_buffer::shared_buffer(const std::string& str) {
    m_data.reset(new value_type[str.size()], array_deleter<value_type>());
    std::copy(str.cbegin(), str.cend(), m_data.get());
    m_size = str.size();
}


rrc::shared_buffer::shared_buffer(rrc::shared_buffer::size_type size, const rrc::shared_buffer::value_type& val) {
    m_data.reset(new value_type[size], array_deleter<value_type>());
    m_size = size;
    this->fill(val);
}


template <class InputIterator>
rrc::shared_buffer::shared_buffer(InputIterator first, InputIterator last) {
    size_t size = (size_t) std::distance(first, last);
    m_data.reset(new value_type[size], array_deleter<value_type>());
    m_size = size;
    std::copy(first, last, m_data.get());
}


rrc::shared_buffer::value_type& rrc::shared_buffer::operator[](rrc::shared_buffer::size_type n) {
    this->ensure_unique();
    value_type* data = m_data.get();
    return data[n];
}


const rrc::shared_buffer::value_type& rrc::shared_buffer::operator[](rrc::shared_buffer::size_type n) const {
    this->ensure_initialized();
    const value_type* data = m_data.get();
    return data[n];
}


void rrc::shared_buffer::fill(const rrc::shared_buffer::value_type& value) {
    this->ensure_unique();
    std::fill_n(m_data.get(), size(), value);
}


rrc::shared_buffer::size_type rrc::shared_buffer::size() const noexcept {
    this->ensure_initialized();
    return m_size;
}


rrc::shared_buffer::value_type* rrc::shared_buffer::data() {
    return m_data.get();
}


const rrc::shared_buffer::value_type* rrc::shared_buffer::data() const {
    this->ensure_initialized();
    return m_data.get();
}


rrc::shared_buffer::const_iterator rrc::shared_buffer::begin() const {
    this->ensure_initialized();
    return const_iterator(m_data.get());
}


rrc::shared_buffer::const_iterator rrc::shared_buffer::end() const {
    this->ensure_initialized();
    return const_iterator(m_data.get() + this->size());
}


rrc::shared_buffer::const_reverse_iterator rrc::shared_buffer::rbegin() const {
    this->ensure_initialized();
    return const_reverse_iterator(end());
}


rrc::shared_buffer::const_reverse_iterator rrc::shared_buffer::rend() const {
    this->ensure_initialized();
    return const_reverse_iterator(begin());
}


rrc::shared_buffer::const_iterator rrc::shared_buffer::cbegin() const {
    this->ensure_initialized();
    return const_iterator(m_data.get());
}


rrc::shared_buffer::const_iterator rrc::shared_buffer::cend() const {
    this->ensure_initialized();
    return const_iterator(m_data.get() + this->size());
}


rrc::shared_buffer::const_reverse_iterator rrc::shared_buffer::crbegin() const {
    this->ensure_initialized();
    return const_reverse_iterator(end());
}


rrc::shared_buffer::const_reverse_iterator rrc::shared_buffer::crend() const {
    this->ensure_initialized();
    return const_reverse_iterator(begin());
}


bool rrc::shared_buffer::operator==(const rrc::shared_buffer& rhs) const {
    this->ensure_initialized();
    return m_size == rhs.m_size && std::equal(this->cbegin(), this->cend(), rhs.cbegin());
}


bool rrc::shared_buffer::operator!=(const rrc::shared_buffer& rhs) const {
    return !(*this == rhs);
}


bool rrc::shared_buffer::operator==(const std::string& rhs) const {
    this->ensure_initialized();
    return m_size == rhs.size() && std::equal(m_data.get(), m_data.get() + m_size, rhs.begin());
}


bool rrc::shared_buffer::operator!=(const std::string& rhs) const {
    return !(*this == rhs);
}


void rrc::shared_buffer::ensure_initialized() const {
    if(!m_data) {
        m_data.reset(new value_type());
        *m_data = '\0';
        m_size = 1;
    }
}


void rrc::shared_buffer::ensure_unique() {
    this->ensure_initialized();
    if(!m_data.unique()) {
        value_type* old_ptr = m_data.get();
        m_data.reset(new value_type[m_size], array_deleter<value_type>());
        std::copy(old_ptr, old_ptr + m_size, m_data.get());
    }
}


namespace rrc {
    std::ostream& operator<<(std::ostream& os, const rrc::shared_buffer& buffer) {
        os << buffer.data();
        return os;
    }
}
