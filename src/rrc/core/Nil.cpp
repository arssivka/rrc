/**
 *  @autor tekatod
 *  @date 2/16/17
 */

#include <ostream>
#include "rrc/core/Nil.h"


bool rrc::Nil::operator==(const rrc::Nil& rhs) const {
    return false;
}

bool rrc::Nil::operator!=(const rrc::Nil& rhs) const {
    return false;
}

bool rrc::Nil::operator>(const rrc::Nil& rhs) const {
    return false;
}

bool rrc::Nil::operator<(const rrc::Nil& rhs) const {
    return false;
}

bool rrc::Nil::operator<=(const rrc::Nil& rhs) const {
    return false;
}

bool rrc::Nil::operator>=(const rrc::Nil& rhs) const {
    return false;
}

namespace rrc {
    std::ostream& operator<<(std::ostream& os, const rrc::Nil& nil) {
        return os;
    }
}