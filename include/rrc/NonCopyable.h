/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


namespace rrc {
    class NonCopyable {
    private:
        NonCopyable(const NonCopyable& other) = delete;

        NonCopyable& operator=(const NonCopyable& other) = delete;

    };
}