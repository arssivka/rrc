/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#pragma once


#include <ostream>

namespace rrc {
    class Number {
    public:
        Number(double value = 0.0);

        Number(const Number&) = default;

        Number(Number&&) = default;

        inline double get() const;

        inline void set(double value);

        inline Number& operator=(const Number&) = default;

        inline Number& operator=(Number&&) = default;

        inline bool operator==(const Number& rhs) const;

        inline bool operator!=(const Number& rhs) const;

        inline bool operator<(const Number& rhs) const;

        inline bool operator>(const Number& rhs) const;

        inline bool operator<=(const Number& rhs) const;

        inline bool operator>=(const Number& rhs) const;

        inline operator double();

        friend std::ostream& operator<<(std::ostream& os, const rrc::Number& number);

    private:
        double mValue;
    };
}

