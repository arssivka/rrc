/**
 *  @autor arssivka
 *  @date 3/16/17
 */

#include <rrc/service_mechanism.h>


rrc::service_mechanism::service_mechanism(rrc::abstract_launcher& launcher)
        : mechanism(launcher) {}


void rrc::service_mechanism::add_service(std::string key,
                                         rrc::service_callback callback,
                                         rrc::result_callback result) {
    mechanism::template enqueue_task<SERVICE_CHANGES_PRIORITY>(
            &base_type::add_service,
            std::move(key),
            std::move(callback),
            std::move(result)
    );
}


void rrc::service_mechanism::remove_service(rrc::service_callback callback,
                                            rrc::result_callback result) {
    mechanism::template enqueue_task<SERVICE_CHANGES_PRIORITY>(
            &base_type::remove_service,
            std::move(callback),
            std::move(result)
    );
}


void rrc::service_mechanism::call(const std::string& key,
                                  rrc::shared_buffer input,
                                  rrc::service_result_callback listener) {
    mechanism::template enqueue_task<SERVICE_CALL_PRIORITY>(
            &base_type::call,
            std::move(key),
            std::move(input),
            std::move(listener)
    );
}


std::vector<std::string> rrc::service_mechanism::keys() const {
    return mechanism::call(std::mem_fn(&service_holder::keys));
}
