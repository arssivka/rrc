/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#pragma once

#include <ostream>

namespace rrc {
    class Boolean {
    public:
        Boolean(bool value = false);

        Boolean(const Boolean&) = default;

        Boolean(Boolean&&) = default;

        bool get() const;

        void set(bool value);

        Boolean& operator=(const Boolean&) = default;

        Boolean& operator=(Boolean&&) = default;

        bool operator==(const Boolean& rhs) const;

        bool operator!=(const Boolean& rhs) const;

        friend std::ostream& operator<<(std::ostream& os, Boolean& boolean);

        operator bool() const;


    private:
        bool mValue;
    };
}
