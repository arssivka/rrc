/**
 *  @autor Nikita Somenkov
 *  @date 08/10/2016
 */
#pragma once

#include "IODevice.h"

namespace rrc {

    template <typename Implementation>
    class Socket_ : public IODevice
    {

    public:
        Socket_(IOService &service);

        virtual void open();
        virtual bool isOpen();

        virtual void close();

        virtual void read(IOBufferPtr buffer, Callback &callback);
        virtual void write(const IOBufferPtr buffer, Callback &callback);

    private:
        Implementation mImpl;
    };

}



