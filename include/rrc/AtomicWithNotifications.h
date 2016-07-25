/**
 * @author arssivka
 * @date 7/22/16
 */

#pragma once


#include <mutex>
#include <condition_variable>
#include <atomic>

namespace rrc {
    template <class T, class Mut = std::mutex>
    class AtomicWithNotifications {
    public:
        typedef T Data;
        typedef std::atomic<T> Atomic;

        AtomicWithNotifications() = default;

        template <class Targ>
        AtomicWithNotifications(Targ&& arg)
                : mAtomic(std::forward((arg))) { }

        template <class Targ>
        void store(Targ&& val, std::memory_order order = std::memory_order_seq_cst) {
            mAtomic.store(std::forward(val), order);
            mCv.notify_all();
        }

        T load(std::memory_order order = std::memory_order_seq_cst) const {
            return mAtomic.load(order);
        }

        std::unique_lock<Mut> wait() {
            std::unique_lock<Mut> lock(mMutex);
            mCv.wait(lock);
            return std::move(lock);
        }

        template <class Predicate>
        std::unique_lock<Mut> wait(Predicate&& pred) {
            auto bound = std::bind(std::forward<Predicate>(pred), mAtomic);
            std::unique_lock<Mut> lock(mMutex);
            mCv.wait(lock, bound);
            return std::move(lock);
        }

        template <class Rep, class Period>
        std::unique_lock<Mut> waitFor(const std::chrono::duration<Rep,Period>& relTime) {
            std::unique_lock<Mut> lock(mMutex);
            mCv.wait_for(lock, relTime);
            return std::move(lock);
        }

        template <class Rep, class Period, class Predicate>
        std::unique_lock<Mut> waitFor(const std::chrono::duration<Rep,Period>& relTime, Predicate&& pred) {
            auto bound = std::bind(std::forward<Predicate>(pred), mAtomic);
            std::unique_lock<Mut> lock(mMutex);
            mCv.wait_for(lock, relTime, bound);
            return std::move(lock);
        }

        template <class Clock, class Duration>
        std::unique_lock<Mut> waitUntil(const std::chrono::time_point<Clock,Duration>& abs_time) {
            std::unique_lock<Mut> lock(mMutex);
            mCv.wait_until(lock, abs_time);
            return std::move(lock);
        }

        template <class Clock, class Duration, class Predicate>
        std::unique_lock<Mut> waitUntil(const std::chrono::time_point<Clock,Duration>& abs_time, Predicate&& pred) {
            std::unique_lock<Mut> lock(mMutex);
            mCv.wait_until(lock,  abs_time, std::forward<Predicate>(pred));
            return std::move(lock);
        }


    private:
        Mut mMutex;
        std::condition_variable mCv;
        std::atomic<T> mAtomic;
    };
}


