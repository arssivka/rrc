/**
 *  @autor tekatod
 *  @date 7/18/16
 */
#pragma once

#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <algorithm>
#include <vector>
#include "NonCopyable.h"

namespace rrc {
    template<typename K, typename D, typename Hash=std::hash<K> >
    class TSLookUp : private NonCopyable {
    public:
        typedef K Key;
        typedef D Data;
        typedef std::shared_ptr<D> SPtr;
        typedef Hash Hash;

        TSLookUp(
                unsigned numBuckets = 19, const Hash& hasher = Hash()) :
                mBuckets(numBuckets), mHasher(hasher) {
            for (unsigned i = 0; i < numBuckets; ++i) {
                mBuckets[i].reset(new BucketType);
            }
        }

        template <class D1>
        SPtr get(const K& key, D1&& defaultValue) const {
            return this->getBucket(key).valueFor(key, std::forward(defaultValue));
        }

        SPtr get(const K& key) const {
            return this->getBucket(key).valueFor(key);
        }

        D detach(const K& key) const {
            return this->getBucket(key).detachFor(key);
        }

        template <class D1>
        void set(const K& key, D1&& value) {
            this->getBucket(key).addOrUpdate(key, std::forward(value));
        }

        bool remove(const K & key) {
            return this->getBucket(key).remove(key);
        }

    private:
        class BucketType {
        public:
            template <class D1>
            SPtr valueFor(const K& key, D1&& defaultValue) const {
                std::lock_guard<std::mutex> lock(mMutex);
                BucketIterator const foundEntry = this->findEntryFor(key);
                if (foundEntry == mName.end()) {
                    mName.emplace_back(BucketValue(key, std::forward(defaultValue)));
                    return std::make_shared<D>(defaultValue);
                } else {
                    return std::make_shared<D>(foundEntry->second);
                }
            }

            SPtr valueFor(const K& key) const {
                std::lock_guard<std::mutex> lock(mMutex);
                BucketIterator const foundEntry = this->findEntryFor(key);
                return (foundEntry == mName.end())
                       ? nullptr
                       : std::make_shared<D>(foundEntry->second);
            }

            D detachFor(const K& key) {
                std::lock_guard<std::mutex> lock(mMutex);
                BucketIterator const foundEntry = this->findEntryFor(key);
                return (foundEntry == mName.end())
                       ? D()
                       : std::move(foundEntry->second);
            }

            template <class D1>
            void addOrUpdate(const K& key, D1&& value) {
                std::lock_guard<std::mutex> lock(mMutex);
                const BucketIterator found = this->findEntryFor(key);
                if (found == mName.end()) {
                    mName.emplace_back(BucketValue(key, std::forward(value)));
                } else {
                    found->second = std::forward(value);
                }
            }

            bool remove(K const &key) {
                std::unique_lock<std::mutex> lock(mMutex);
                const BucketIterator found = this->findEntryFor(key);
                if (found != mName.end()) {
                    mName.erase(found);
                    return true;
                }
                return false;
            }

        private:
            BucketIterator findEntryFor(K const &key) const {
                return std::find_if(mName.begin(), mName.end(),
                                    [&](const BucketValue& item) {
                                        return item.first == key;
                                    });
            }

            typedef std::pair<K, D> BucketValue;
            typedef std::list<BucketValue> BucketData;
            typedef typename BucketData::iterator BucketIterator;
            mutable BucketData mName;
            mutable std::mutex mMutex;
        };

        BucketType &getBucket(K const& key) const {
            std::size_t const bucket_index = mHasher(key) % mBuckets.size();
            return *mBuckets[bucket_index];
        }

        std::vector<std::unique_ptr<BucketType> > mBuckets;
        Hash mHasher;
    };
}