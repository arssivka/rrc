/**
 *  @autor arssivka
 *  @date 3/1/17
 */
#pragma once


#include "mechanism.h"
#include "finalizer.h"

namespace rrc {
    template <class Q>
    class finalizer_mechanism : public mechanism<finalizer, Q, 1> {
    public:
        enum {
            CHANGE_LISTENERS_PRIORITY
        };

        finalizer_mechanism(abstract_launcher& launcher)
                : mechanism<finalizer, Q, 1>(launcher) {
            launcher.enqueue_finalize_task([this] {
                this->apply_changes();
                this->call(std::mem_fn(&finalizer::exec_all));
            });
        }

        void add_finalize_callback(std::shared_ptr<finalizer::callback_type> callback_ptr) {
            this->enqueue_task(
                    CHANGE_LISTENERS_PRIORITY,
                    &finalizer::add_callback,
                    std::move(callback_ptr)
            );
        }

        void remove_finalize_callback(std::shared_ptr<finalizer::callback_type> callback_ptr) {
            this->enqueue_task(
                    CHANGE_LISTENERS_PRIORITY,
                    &finalizer::remove_callback,
                    std::move(callback_ptr)
            );
        }

    };
}

