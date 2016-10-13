/**
 *  @autor Nikita Somenkov
 *  @date 08/10/2016
 */
#pragma once

#include "IOBuffer.h"
#include "IOService.h"
#include "Definitions.h"
#include "IOError.h"

namespace rrc {

    typedef std::function<IOError()> AsyncOperation;
    typedef std::function<void(IOError)> Callback;

    class IODevice
    {
    public:
        IODevice(IOService &service);

        virtual void open() = 0;
        virtual bool isOpen() = 0;

        virtual void close() = 0;

        virtual void read(IOBufferPtr buffer, Callback &callback) = 0;
        virtual void write(const IOBufferPtr buffer, Callback &callback) = 0;

    protected:
        void addAsyncOperation(AsyncOperation &&operation, const Callback &callback);

    private:
        IOService &mIoService;
    };

}


