/**
 *  @autor Nikita Somenkov
 *  @date 08/10/2016
 */
#include "rrc/io/IODevice.h"

rrc::IODevice::IODevice(rrc::IOService &service) : mIoService(service) {

}

void rrc::IODevice::addAsyncOperation(rrc::AsyncOperation &&operation,
                                      const rrc::Callback &callback)
{
    mIoService.addAsyncCommand([operation, callback](){
        IOError error = operation();
        callback(error);
    });
}
