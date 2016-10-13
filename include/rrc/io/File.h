/**
 *  @autor Nikita Somenkov
 *  @date 08/10/2016
 */
#pragma once

#include <string>

#include "IODevice.h"

namespace rrc
{
    template <typename Implementation>
    class File_ : public IODevice {
    public:
        File_(IOService &service, const std::string &path, Mode mode) :
            IODevice(service), mPath(path), mMode(mode) { }

        virtual void open() {
            mImpl.open(mPath.c_str(), mMode);
        }

        virtual bool isOpen() {
            return mImpl.isOpen();
        }

        virtual void close() {
            mImpl.close();
        }

        virtual void read(IOBufferPtr buffer, Callback &callback) {
            this->addAsyncOperation([this, buffer]() -> IOError {
                return this->mImpl.read(buffer->data(), buffer->size());
            }, callback);
        }

        virtual void write(const IOBufferPtr buffer, Callback &callback) {
            this->addAsyncOperation([this, buffer]() -> IOError {
                return this->mImpl.write(buffer->data(), buffer->size());
            }, callback);
        }

    private:
        Mode mMode;
        std::string mPath;
        Implementation mImpl;
    };
};


#include "unix/UnixFile.h"
namespace rrc {
    typedef File_<unix::UnixFile> File;
}