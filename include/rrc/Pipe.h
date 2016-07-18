/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include "ID.h"
#include "Message.h"
#include "NonCopyable.h"

namespace rrc {
    template <class T>
    class Pipe : private NonCopyable {
    public:
        typedef T type;

        Pipe(const ID& pipe, const std::string& topic);

        bool isConnected() const;

        void push(Message<T> msg, bool updateTimestamp);

        template <class Func>
        void setCallback(Func&& callback);

    private:
        std::function<void(Message<T>)> mCallback;
    };
}


