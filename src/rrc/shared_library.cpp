/**
 *  @autor arssivka
 *  @date 4/11/17
 */

#include "rrc/shared_library.h"


#if defined(RRC_UNIX)

rrc::shared_library::shared_library(const std::string& filename)
        : m_handle_ptr(dlopen(filename.c_str(), RTLD_LAZY)) {}


rrc::shared_library::~shared_library() {
    if (this->loaded()) {
        dlclose(m_handle_ptr);
    }
}


#endif


bool rrc::shared_library::loaded() const noexcept {
    return m_handle_ptr != nullptr;
}

rrc::shared_library::operator bool() const noexcept {
    return this->loaded();
}
