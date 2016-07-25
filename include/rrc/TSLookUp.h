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

        const SPtr get(const K& key) const {
            return this->getBucket(key).valueFor(key);
        }

        SPtr get(const K& key) {
            return this->getBucket(key).valueFor(key);
        }

        SPtr detach(const K& key) const {
            return this->getBucket(key).detachFor(key);
        }

        void set(const K& key, SPtr value) {
            this->getBucket(key).addOrUpdate(key, std::move(value));
        }

        template <class Value>
        void set(const K& key, Value&& value) {
            this->getBucket(key).addOrUpdate(key, std::make_shared<D>(std::forward<Value>(value)));
        }
        
        bool contains(const K& key) const {
            return this->getBucket(key).contains(key);
        }

        bool remove(const K& key) {
            return this->getBucket(key).remove(key);
        }

    private:
        class BucketType {
        public:
            const SPtr valueFor(const K& key) const {
                std::lock_guard<std::mutex> lock(mMutex);
                const BucketIterator found = this->findEntryFor(key);
                if (found == mData.end()) {
                    mData.emplace_back(BucketValue(key, D()));
                    return mData.back().second;
                } else {
                    return found->second;
                }
            }

            SPtr valueFor(const K& key) {
                std::lock_guard<std::mutex> lock(mMutex);
                const BucketIterator found = this->findEntryFor(key);
                if (found == mData.end()) {
                    mData.emplace_back(key, D());
                    return mData.back().second;
                } else {
                    return found->second;
                }
            }
            
            bool contains(const Key& key) const {
                return this->findEntryFor(key) != mData.end();
            }

            SPtr detachFor(const K& key) {
                std::lock_guard<std::mutex> lock(mMutex);
                BucketIterator const found = this->findEntryFor(key);
                SPtr res = nullptr;
                if (found != mData.end()) {
                    res = std::move(found->second);
                }
                mData.erase(found);
                return res;
            }

            template <class Value>
            void addOrUpdate(const K& key, SPtr value) {
                std::lock_guard<std::mutex> lock(mMutex);
                const BucketIterator found = this->findEntryFor(key);
                if (found == mData.end()) {
                    mData.emplace_back(key, std::move(value));
                } else {
                    found->second = std::move(value);
                }
            }

            bool remove(K const &key) {
                std::unique_lock<std::mutex> lock(mMutex);
                const BucketIterator found = this->findEntryFor(key);
                if (found != mData.end()) {
                    mData.erase(found);
                    return true;
                }
                return false;
            }

        private:
            BucketIterator findEntryFor(const K& key) const {
                return std::find_if(mData.begin(), mData.end(),
                                    [&](const BucketValue& item) {
                                        return item.first == key;
                                    });
            }

            typedef std::pair<K, SPtr> BucketValue;
            typedef std::list<BucketValue> BucketData;
            typedef typename BucketData::iterator BucketIterator;
            mutable BucketData mData;
            mutable std::mutex mMutex;
        };

        BucketType& getBucket(const K& key) const {
            std::size_t const bucket_index = mHasher(key) % mBuckets.size();
            return *mBuckets[bucket_index];
        }

        std::vector<std::unique_ptr<BucketType>> mBuckets;
        Hash mHasher;
    };
}