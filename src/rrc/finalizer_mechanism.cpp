/**
 *  @autor arssivka
 *  @date 3/16/17
 */

#include <rrc/finalizer_mechanism.h>


rrc::finalizer_mechanism::finalizer_mechanism(rrc::abstract_launcher& launcher)
        : mechanism<finalizer, 1>(launcher) {
    launcher.enqueue_finalize_task([this] {
        this->apply_changes();
        this->call(std::mem_fn(&finalizer::exec_and_clear));
    });
}


void rrc::finalizer_mechanism::add_finalize_callback(rrc::finalize_callback callback) {
    this->template enqueue_task<CHANGE_LISTENERS_PRIORITY>(
            &finalizer::add_callback,
            std::move(callback)
    );
}


void rrc::finalizer_mechanism::remove_finalize_callback(rrc::finalize_callback callback) {
    this->template enqueue_task<CHANGE_LISTENERS_PRIORITY>(
            &finalizer::remove_callback,
            std::move(callback)
    );
}
