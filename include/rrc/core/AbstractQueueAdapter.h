/**
 *  @autor arssivka
 *  @date 10/31/16
 */

#pragma once


#include "NonCopyable.h"
#include "Pointer.h"

namespace rrc {
    template <class T>
    class AbstractQueueAdapter : public Pointer<AbstractQueueAdapter<T>>, private NonCopyable {
    public:
        virtual void enqueue(const T& value) = 0;

        virtual void enqueue(T&& value) = 0;

        virtual bool tryDequeue(T& value) = 0;

        virtual ~AbstractQueueAdapter() { }

    };
}