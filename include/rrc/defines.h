/**
 *  @autor arssivka
 *  @date 4/10/17
 */

#pragma once


#include <string>

#if defined(__linux__) || \
        defined(__linux)   || \
        defined(linux)     || \
        defined(__APPLE__)
    #define RRC_EXPORT
    #define RRC_UNIX
#elif defined(_WIN32)
    #define RRC_EXPORT __declspec(dllexport)
    #define RRC_WIN32
#else
    #warning "Unknown target platform"
#endif

namespace rrc {
    const std::string MODULE_ENTRY("rrcmain");
}


