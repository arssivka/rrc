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

        double get() const;

        void set(double value);

        Number& operator=(const Number&) = default;

        Number& operator=(Number&&) = default;

        bool operator==(const Number& rhs) const;

        bool operator!=(const Number& rhs) const;

        bool operator<(const Number& rhs) const;

        bool operator>(const Number& rhs) const;

        bool operator<=(const Number& rhs) const;

        bool operator>=(const Number& rhs) const;

        operator double();

        friend std::ostream& operator<<(std::ostream& os, const rrc::Number& number);

    private:
        double mValue;
    };
}

