/**
 *  @autor arssivka
 *  @date 7/15/16
 */

#pragma once


#include <queue>
#include <forward_list>
#include <mutex>
#include <memory>
#include "NonCopyable.h"

namespace rrc {
    template <class K, class T>
    class TSPriorityQueue : private NonCopyable {
    public:
        typedef K Key;
        typedef T Data;
        typedef std::pair<K, T> Bucket;
        typedef std::shared_ptr<Bucket> BucketSPtr;

        TSPriorityQueue() {}

        template <class B>
        void push(std::shared_ptr<B> data) {
            std::lock_guard<std::mutex> lock(mMutex);
            mQueue.emplace(std::forward<B>(data));
        }

        template <class B>
        void push(B&& data) {
            BucketSPtr sptr = std::make_shared<B>(new B(std::forward<B>(data)));
            std::lock_guard<std::mutex> lock(mMutex);
            mQueue.emplace(std::forward<B>(data));
        }

        BucketSPtr pop() {
            BucketSPtr res = nullptr;
            {
                std::lock_guard<std::mutex> lock(mMutex);
                if (!mQueue.empty()) {
                    res = mQueue.top();
                    mQueue.pop();
                }

            }
            return res;
        }



    private:
        typedef std::priority_queue<BucketSPtr, std::vector<BucketSPtr>, BucketComparator> PriorityQueue;

        class BucketComparator {
        public:
            inline  bool operator()(const BucketSPtr& lhs, const BucketSPtr& rhs) const  {
                return lhs->first > rhs->first;
            }
        };

        PriorityQueue mQueue;
        mutable std::mutex mMutex;
    };
}


