/**
 *  @autor arssivka
 *  @date 4/8/17
 */

#include "rrc/receiver.h"

rrc::receiver::receiver(rrc::receiver::functor&& fn)
        : m_functor(std::move(fn)) {}

void rrc::receiver::receive(const uint8_t* buff, size_t size) {
    m_functor(buff, size);
}
