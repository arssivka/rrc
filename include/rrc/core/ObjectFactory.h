/**
 *  @autor arssivka
 *  @date 2/2/17
 */

#pragma once


#include <functional>
#include <memory>

namespace rrc {
    // TODO Tests and docs
    template <class T>
    class ObjectFactory {
    public:
        template <class I, class... Args>
        ObjectFactory(Args&&... args) {
            static_assert(std::is_base_of<T, I>::value,
                          "Constructed class must be inherited from factory template class");
            mFactoryMethod = [args...]() -> T* {
                return new I(args...);
            };
        }

        std::unique_ptr<T> createUniquePointer() const {
            return std::unique_ptr<T>(mFactoryMethod());
        }

        std::shared_ptr<T> createSharedPointer() const {
            return std::shared_ptr<T>(mFactoryMethod());
        }

    private:
        std::function<T*()> mFactoryMethod;

    };
}