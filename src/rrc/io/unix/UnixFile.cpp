/**
 *  @autor nikitas
 *  @date 10/12/16
 */

#include <fcntl.h>
#include <unistd.h>

#include "rrc/io/unix/UnixFile.h"

rrc::unix::UnixFile::UnixFile() : mFileDescriptor(-1) {

}

rrc::unix::UnixFile::UnixFile(const std::string &path, rrc::Mode mode) {
    this->open(path, mode);
}

void rrc::unix::UnixFile::open(const std::string &path, rrc::Mode mode) {
    mFileDescriptor = ::open(path.c_str(), O_RDWR); // TODO: make tr from Mode enum -> UnixConst
}

void rrc::unix::UnixFile::close() {
    ::close(mFileDescriptor);
}

bool rrc::unix::UnixFile::isOpen() {
    return mFileDescriptor != -1;
}

rrc::IOError rrc::unix::UnixFile::read(char *buffer, size_t size) {
    ssize_t read = ::read(mFileDescriptor, buffer, size);
    return IOError(read == -1, "File::read");
}

rrc::IOError rrc::unix::UnixFile::write(const char *buffer, size_t size) {
    ssize_t wrote = ::write(mFileDescriptor, buffer, size);
    return IOError(wrote == -1, "File::write");
}
