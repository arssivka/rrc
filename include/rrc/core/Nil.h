/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#pragma once


namespace rrc {
    class Nil {
    public:
        Nil() = default;

        bool operator==(const Nil& rhs) const;

        bool operator!=(const Nil& rhs) const;

        bool operator>(const Nil& rhs) const;

        bool operator<(const Nil& rhs) const;

        bool operator<=(const Nil& rhs) const;

        bool operator>=(const Nil& rhs) const;

        friend std::ostream& operator<<(std::ostream& os, const rrc::Nil& nil);
    };
}


