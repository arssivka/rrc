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
        typedef Hash Hash;

        TSLookUp(
                unsigned num_buckets = 19, Hash const &hasher_ = Hash()) :
                m_buckets(num_buckets), m_hasher(hasher_) {
            for (unsigned i = 0; i < num_buckets; ++i) {
                m_buckets[i].reset(new BucketType);
            }
        }

        D get(K const &key, D const &default_value = D()) const {
            return get_bucket(key).valueFor(key, default_value);
        }

        void addOrUpdate(K const &key, D const &value) {
            get_bucket(key).addOrUpdate(key, value);
        }

        void remove(K const &key) {
            get_bucket(key).remove(key);
        }

    private:
        class BucketType {
        public:
            D valueFor(K const &key, D const &default_value) const {
                std::lock_guard<std::mutex> lock(m_mutex);
                BucketIterator const found_entry = this->findEntryFor(key);
                return (found_entry == m_name.end()) ?
                       default_value : found_entry->second;
            }

            void addOrUpdate(K const &key, D const &value) {
                std::unique_lock<std::mutex> lock(m_mutex);
                BucketIterator const found_entry = this->findEntryFor(key);
                if (found_entry == m_name.end()) {
                    m_name.push_back(BucketValue(key, value));
                }
                else {
                    found_entry->second = value;
                }
            }

            void remove(K const &key) {
                std::unique_lock<std::mutex> lock(m_mutex);
                BucketIterator const found_entry = this->findEntryFor(key);
                if (found_entry != m_name.end()) {
                    m_name.erase(found_entry);
                }
            }

        private:
            BucketIterator findEntryFor(K const &key) const {
                return std::find_if(m_name.begin(), m_name.end(),
                                    [&](BucketValue const &item) {
                                        return item.first == key;
                                    });
            }

            typedef std::pair<K, D> BucketValue;
            typedef std::list<BucketValue> BucketData;
            typedef typename BucketData::iterator BucketIterator;
            mutable BucketData m_name;
            mutable std::mutex m_mutex;
        };

        BucketType &get_bucket(K const &key) const {
            std::size_t const bucket_index = m_hasher(key) % m_buckets.size();
            return *m_buckets[bucket_index];
        }

        std::vector<std::unique_ptr<BucketType> > m_buckets;
        Hash m_hasher;
    };
}