/**
 *  @autor arssivka
 *  @date 2/7/17
 */

#pragma once


#include <unordered_map>
#include "Service.h"

namespace rrc {
    template <class ServiceName>
    class ServiceHolder {
    public:
        ServiceHolder() {
            // TODO: Test it
            mServiceHash.max_load_factor(0.8);
        }

        void addService(const ServiceName& name, std::shared_ptr<Service> service) {
            mServiceHash.insert({name, std::move(service)});
        }

        void removeService(const ServiceName& name, const std::weak_ptr<Service> service) {
            auto lock = service.lock();
            if (lock != nullptr) {
//                auto it = mServiceHash.begin();
//                while (it != mServiceHash.end()) {
//                    if (it->first == name && it->second == lock) {
//                        mServiceHash.erase(it);
//                    } else {
//                        ++it;
//                    }
//                }
                auto range = mServiceHash.equal_range(name);
                auto it = range.first;
                while (it != range.second) {
                    if (it->second == lock) {
                        mServiceHash.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
        }

        void call(const ServiceName& name, std::shared_ptr<TaskHub<Buffer>> resultHub, std::shared_ptr<Buffer> input) {
            auto range = mServiceHash.equal_range(name);
            for (auto it = range.first; it != range.second; ++it) {
                auto& service = it->second;
                service->call(resultHub, input);
            }
        }

        std::vector<ServiceName> getNames() const {
            std::vector<ServiceName> names;
            names.reserve(mServiceHash.size());
            for (auto&& keyPair : mServiceHash) {
                names.push_back(keyPair.first);
            }
            return names;
        }

    private:
        std::unordered_multimap<ServiceName, std::shared_ptr<Service>> mServiceHash;
    };
}


