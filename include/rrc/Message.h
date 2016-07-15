/**
 *  @autor arssivka
 *  @date 7/11/16
 */

#pragma once


#include <memory>

namespace rrc {
    template <class T>
    class Message {
    public:
        typedef std::shared_ptr<Message<T>> Ptr;

        template <typename... Args>
        static Ptr create(Args... args) {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }

        T& getData() {
            return mData;
        }

    private:
        T mData;

    };
}


