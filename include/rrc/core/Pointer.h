/**
 *  @autor arssivka
 *  @date 10/31/16
 */

#pragma once


#include <memory>

namespace rrc {
    template<class T>
    class Pointer {
    public:
        typedef std::shared_ptr<T> Ptr;

    };
}