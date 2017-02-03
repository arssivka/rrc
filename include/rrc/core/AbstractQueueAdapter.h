/**
 *  @autor arssivka
 *  @date 10/31/16
 */

#pragma once


#include "NonCopyable.h"

namespace rrc {
    // TODO: Docs
    template <class T>
    class AbstractQueueAdapter : private NonCopyable {
    public:
        virtual void enqueue(const T& value) = 0;

        virtual void enqueue(T&& value) = 0;

        virtual bool tryDequeue(T& value) = 0;

        virtual ~AbstractQueueAdapter() { }

    };
}