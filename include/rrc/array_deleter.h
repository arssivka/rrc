/**
 *  @autor arssivka
 *  @date 3/16/17
 */

#pragma once


namespace rrc {
    template <class T>
    class array_deleter {
    public:
        typedef T value_type;

        void operator()(value_type* ptr) {
            delete [] ptr;
        }
    };
}