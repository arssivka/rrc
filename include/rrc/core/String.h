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

        inline String& operator=(const String&) = default;

        inline String& operator=(String&&) = default;

        inline const std::string& get() const;

        inline void set(const std::string& string);

        inline size_t getSize() const;

        inline bool isEmpty() const;

        inline bool operator==(const String& rhs) const;

        inline bool operator!=(const String& rhs) const;

        inline const char& operator[](size_t index);

        inline const auto begin() const noexcept;

        inline const auto end() const noexcept;

        inline const auto rbegin() const noexcept;

        inline const auto rend() const noexcept;

        inline const auto cbegin() const noexcept;

        inline const auto cend() const noexcept;

        inline const auto crbegin() const noexcept;

        inline const auto crend() const noexcept;

        friend std::ostream& operator<<(std::ostream& os, const String& string);

        inline operator const std::string&();

    private:
        std::string mString;

    };
}


