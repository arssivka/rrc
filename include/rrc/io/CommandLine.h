/**
 *  @autor Nikita Somenkov
 *  @date 08/10/2016
 */
#pragma once

#include "IODevice.h"

namespace rrc {

    template <typename Implementation>
    class CommandLine_ : public IODevice
    {
    public:
        CommandLine_(IOService &service, Console console);

        virtual void open();
        virtual bool isOpen();

        virtual void close();

        virtual void read(IOBufferPtr buffer, Callback &callback);
        virtual void write(const IOBufferPtr buffer, Callback &callback);

    private:
        Implementation mImpl;
    };

}

//#include "unix/UnixCommandLine.h"
//namespace rrc {
//    typedef CommandLine_<unix::UnixCommandLine> CommandLine;
//}


