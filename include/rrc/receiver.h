/**
 *  @autor arssivka
 *  @date 4/8/17
 */

#pragma once


#include <cstdint>
#include <cstddef>
#include <functional>

namespace rrc {
    class receiver {
    public:
        using functor = std::function<void(const uint8_t*, size_t)>;

        receiver(functor&& fn);

        receiver(const receiver&) = delete;

        receiver& operator=(const receiver&) = delete;

        void receive(const uint8_t* buff, size_t size);

    private:
        std::function<void(const uint8_t*, size_t)> m_functor;

    };
}


