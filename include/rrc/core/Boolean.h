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

        inline bool get() const;

        inline void set(bool value);

        inline Boolean& operator=(const Boolean&) = default;

        inline Boolean& operator=(Boolean&&) = default;

        inline bool operator==(const Boolean& rhs) const;

        inline bool operator!=(const Boolean& rhs) const;

        friend std::ostream& operator<<(std::ostream& os, Boolean& boolean);

        inline operator bool() const;


    private:
        bool mValue;
    };
}


