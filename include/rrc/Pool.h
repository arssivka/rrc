/**
 *  @autor arssivka
 *  @date 7/11/16
 */

#pragma once


#include <bits/allocator.h>

template <class T>
class Pool
        : public std::allocator<T> {
public:
    Pool(size_t pageSize);

    allocate

private:

};


