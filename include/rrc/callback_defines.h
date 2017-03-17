/**
 *  @autor arssivka
 *  @date 3/16/17
 */

#pragma once


#include <string>
#include "shared_buffer.h"
#include "shared_function.h"
#include "result_code.h"

namespace rrc {
    typedef shared_function<void(const shared_buffer&)> topic_callback;
    typedef shared_function<void(result_code, const shared_buffer&)> service_result_callback;
    typedef shared_function<result_code(const shared_buffer&, shared_buffer&)> service_callback;
    typedef shared_function<void()> finalize_callback;
    typedef shared_function<void(result_code)> result_callback;
    typedef shared_function<void(result_code, const std::string& key)> key_callback;
}