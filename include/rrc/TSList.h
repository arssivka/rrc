/**
 *  @autor arssivka
 *  @date 7/19/16
 */

#pragma once


#include <memory>
#include "NonCopyable.h"

namespace rrc {
    template <class T>
    class TSList : private NonCopyable {
    public:
        typedef T Data;
        typedef std::shared_ptr<T> SPtr;

        template <class T1>
        void pushBack(T1&& data);

        void pushBack(SPtr data);

        template <class Func>
        void removeIf(Func&& func);

        template <class Func>
        void applyWhile(Func&& func);

    private:

    };
}


