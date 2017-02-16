/**
 *  @autor arssivka
 *  @date 2/15/17
 */

#pragma once


#include <unordered_map>
#include <list>
#include "TaskHub.h"
#include "Table.h"

namespace rrc {
    template <class K>
    class SettingsHolder {
    public:
        typedef K Key;
        typedef TaskHub<Table> Listener;

        SettingsHolder() = default;

        void removeTable(const K& key) {
            auto found = mTableHash.find(key);
            if (found != mTableHash.end()) {
                mTableHash.erase(found);
                this->notify(key, Table());
            }
        }

        Table getTable(const K& key) const {
            auto found = mTableHash.find(key);
            if (found == mTableHash.end()) {
                return Table();
            }
            return found->second;
        }

        template <class Ka, class T>
        void setTable(Ka&& key, T&& table) {
            this->notify(key, table);
            mTableHash.emplace({std::forward<Ka>(key), std::forward<T>(table)});
        }

        bool isExists(const K& key) const {
            auto found = mTableHash.find(key);
            return found != mTableHash.end();
        }

        std::vector<K> getNames() const {
            std::vector<K> names;
            names.reserve(mTableHash.size());
            for (auto&& table : mTableHash) {
                names.push_back(table.first);
            }
            return names;
        }

        void addListener(const K& key, std::shared_ptr<Listener> listener) {
            mListenersHash.emplace({key, std::move(listener)});
        }

        void removeListener(const K& key, std::weak_ptr<Listener> lisneter) {
            auto lock = lisneter.lock();
            if (lock != nullptr) {
                auto range = mListenersHash.equal_range(key);
                auto found = std::find(range.first, range.second, lock);
                mListenersHash.erase(found, mListenersHash.end());
            }
        }


    private:
        void notify(const Key& name, const Table& table) {
            auto range = mListenersHash.equal_range(name);
            auto toRemove = std::remove_if(range.first, range.end, [&table](auto& listener) {
                return !listener->enqueueTask(table);
            });
            mListenersHash.erase(toRemove, mListenersHash.end());
        }

    private:
        std::unordered_map<K, Table> mTableHash;
        std::unordered_multimap<K, std::shared_ptr<Listener>> mListenersHash;
    };
}


