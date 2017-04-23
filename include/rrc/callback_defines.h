/**
 *  @autor arssivka
 *  @date 3/16/17
 */

#pragma once


#include <string>
#include "string.h"
#include "shared_function.h"
#include "result_code.h"

namespace rrc {
    typedef shared_function<void(const string&)> topic_callback;
    typedef shared_function<void(result_code, const string&)> service_result_callback;
    typedef shared_function<result_code(const string&, string&)> service_callback;
    typedef shared_function<void()> finalize_callback;
    typedef shared_function<void(result_code)> result_callback;
    typedef shared_function<void(result_code, const std::string& key)> key_callback;
}