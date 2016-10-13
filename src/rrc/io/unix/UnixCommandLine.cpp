/**
 *  @autor nikitas
 *  @date 10/12/16
 */
#include <unistd.h>
#include <rrc/io/IOError.h>

#include "rrc/io/unix/UnixCommandLine.h"

rrc::unix::UnixCommandLine::UnixCommandLine() : mClDescriptor(-1) {

}

rrc::unix::UnixCommandLine::UnixCommandLine(rrc::Console console) :
        mClDescriptor(parseConsole(console)) { }

void rrc::unix::UnixCommandLine::open(rrc::Console console) {
    mClDescriptor = parseConsole(console);
}

bool rrc::unix::UnixCommandLine::isOpen() {
    return mClDescriptor != -1;
}

rrc::IOError rrc::unix::UnixCommandLine::read(char *buffer, size_t size) {
    ssize_t read = ::read(mClDescriptor, buffer, size);
    return IOError(mClDescriptor == -1 || read == -1, "CommandLine::read");
}

rrc::IOError rrc::unix::UnixCommandLine::write(const char *buffer, size_t size) {
    ssize_t wrote = ::write(mClDescriptor, buffer, size);
    return IOError(mClDescriptor == -1 || wrote == -1, "CommandLine::write");
}

int rrc::unix::UnixCommandLine::parseConsole(rrc::Console console) {
    switch (console) {
        case Console::Input:
            return STDIN_FILENO;
        case Console::Ouput:
            return STDOUT_FILENO;
        case Console::Error:
            return STDERR_FILENO;
    }
}
