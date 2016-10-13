/**
 *  @autor nikitas
 *  @date 10/12/16
 */
#pragma once

#include <string>

#include "rrc/io/Definitions.h"
#include "rrc/io/IOError.h"

namespace rrc {
namespace unix {

    class UnixFile
    {
    public:
        UnixFile();
        UnixFile(const std::string &path, Mode mode);

        void open(const std::string &path, Mode mode);
        void close();
        bool isOpen();

        IOError read(char *buffer, size_t size);
        IOError write(const char *buffer, size_t size);

    private:
        int mFileDescriptor;
    };


} // unix
} // rrc

