/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#pragma once


#include <string>

namespace rrc {
    class String {
    public:
        String() = default;

        String(const String&) = default;

        String(String&&) = default;

        String(const std::string& string);

        String(std::string&& string);

        String(const std::string& string, size_t position, size_t length);

        String(const char* cstring);

        String(size_t n, char c);

        template <class InputIterator>
        String(InputIterator first, InputIterator last)
                : mString(first, last) {}

        String(std::initializer_list<char> initializerList);

        String& operator=(const String&) = default;

        String& operator=(String&&) = default;

        const std::string& get() const;

        void set(const std::string& string);

        size_t getSize() const;

        bool isEmpty() const;

        bool operator==(const String& rhs) const;

        bool operator!=(const String& rhs) const;

        const char& operator[](size_t index);

        std::string::const_iterator begin() const noexcept;

        std::string::const_iterator end() const noexcept;

        std::string::const_reverse_iterator rbegin() const noexcept;

        std::string::const_reverse_iterator rend() const noexcept;

        std::string::const_iterator cbegin() const noexcept;

        std::string::const_iterator cend() const noexcept;

        std::string::const_reverse_iterator crbegin() const noexcept;

        std::string::const_reverse_iterator crend() const noexcept;

        friend std::ostream& operator<<(std::ostream& os, const String& string);

        operator const std::string&();

    private:
        std::string mString;

    };
}


