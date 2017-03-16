/**
 *  @autor arssivka
 *  @date 3/16/17
 */

#include <rrc/advertising_mechanism.h>


rrc::advertising_mechanism::advertising_mechanism(rrc::abstract_launcher& launcher)
        : mechanism(launcher) {}


void rrc::advertising_mechanism::send_message(std::string topic_key, rrc::shared_buffer message) {
    mechanism::template enqueue_task<SEND_MESSAGE_PRIORITY>(
            &base_type::send_message,
            std::move(topic_key),
            std::move(message)
    );
}


void rrc::advertising_mechanism::add_listener(std::string topic_key, rrc::topic_callback callback,
                                              rrc::result_callback result) {
    mechanism::template enqueue_task<CHANGE_LISTENERS_PRIORITY>(
            &base_type::add_listener,
            std::move(topic_key),
            std::move(callback),
            std::move(result)
    );
}


void rrc::advertising_mechanism::remove_listener(std::string topic_key, rrc::topic_callback callback,
                                                 rrc::result_callback result) {
    mechanism::template enqueue_task<CHANGE_LISTENERS_PRIORITY>(
            &base_type::remove_listener,
            std::move(topic_key),
            std::move(callback),
            std::move(result)
    );
}


std::vector<std::string> rrc::advertising_mechanism::keys() const {
    return mechanism::call(mem_fn(&base_type::keys));
}
