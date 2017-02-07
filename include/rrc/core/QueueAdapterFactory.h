/**
 *  @autor arssivka
 *  @date 2/2/17
 */

#pragma once


#include <functional>
#include <memory>
#include "AbstractQueueAdapter.h"
#include <utility>

namespace rrc {

    // TODO Tests and docs
    template <class T>
    class QueueAdapterFactory {
    public:

        template <class I, class... Args>
        static QueueAdapterFactory<T> create(Args&&... args) {
            return QueueAdapterFactory<T>(type<I>(), args...);
        }


        QueueAdapterFactory(QueueAdapterFactory&& other) = default;

        QueueAdapterFactory(const QueueAdapterFactory& other) = default;


        std::unique_ptr<AbstractQueueAdapter<T>> createUniquePointer() const {
            return std::unique_ptr<AbstractQueueAdapter<T>>(mFactoryMethod());
        }

        std::shared_ptr<AbstractQueueAdapter<T>> createSharedPointer() const {
            return std::shared_ptr<AbstractQueueAdapter<T>>(mFactoryMethod());
        }

    private:
        template<class U>
        class type {};

        template <class I, class... Args>
        QueueAdapterFactory(type<I>, Args&&... args) {
            static_assert(std::is_base_of<AbstractQueueAdapter<T>, I>::value,
                          "Constructed class must be inherited from factory template class");
            mFactoryMethod = [args...]() -> AbstractQueueAdapter<T>* {
                return new I(args...);
            };
        }

        std::function<AbstractQueueAdapter<T>*()> mFactoryMethod;

    };
}