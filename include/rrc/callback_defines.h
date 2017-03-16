/**
 *  @autor arssivka
 *  @date 3/16/17
 */

#pragma once


#include <string>
#include "shared_buffer.h"
#include "shared_function.h"
#include "status.h"

namespace rrc {
typedef shared_function<void(const shared_buffer&)> topic_callback;
    typedef shared_function<void(status, const shared_buffer&)> service_result_callback;
    typedef shared_function<status(const shared_buffer&, shared_buffer&)> service_callback;
    typedef shared_function<void()> finalize_callback;
    typedef shared_function<void(status)> result_callback;
}