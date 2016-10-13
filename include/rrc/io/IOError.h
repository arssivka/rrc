/**
 *  @autor nikitas
 *  @date 10/13/16
 */
#pragma once

#include <stdexcept>

namespace rrc {

    class IOError : public std::runtime_error {
    public:
        IOError();
        IOError(const IOError &other);
        IOError(bool error, const std::string &msg);

        operator bool () const;

    private:
        bool mError;
    };

}



