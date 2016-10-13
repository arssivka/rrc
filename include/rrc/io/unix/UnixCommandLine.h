/**
 *  @autor nikitas
 *  @date 10/12/16
 */
#pragma once

#include "rrc/io/Definitions.h"
#include <cstddef>
#include <rrc/io/IOError.h>

namespace rrc {
namespace unix {

    class UnixCommandLine
    {
    public:
        UnixCommandLine();
        UnixCommandLine(Console console);

        void open(Console console);
        bool isOpen();

        IOError read(char *buffer, size_t size);
        IOError write(const char *buffer, size_t size);

    private:
        static int parseConsole(Console console);

        int mClDescriptor;
    };


} // unix
} // rrc


