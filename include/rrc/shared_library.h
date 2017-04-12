/**
 *  @autor arssivka
 *  @date 4/11/17
 */

#pragma once

#include "defines.h"
#include <string>

#if defined(RRC_UNIX)
    #include <dlfcn.h>
#endif

namespace rrc {
    class shared_library {
    public:
        shared_library(const std::string& filename);

        ~shared_library();

        bool loaded() const noexcept;


        shared_library(shared_library&&) = default;

        shared_library& operator=(shared_library&&) = default;

        // Non copyable
        shared_library(const shared_library&) = delete;

        shared_library& operator=(const shared_library&) = delete;

        operator bool() const noexcept;

#if defined(RRC_UNIX)
    public:
        template <class T>
        T* get_symbol(const std::string& sym) const noexcept {
            if (m_handle_ptr == nullptr) return nullptr;
            T* ptr = (T*) dlsym(m_handle_ptr, sym.c_str());
            return ptr;
        }


    private:
        void* m_handle_ptr;
#endif
    };
}


