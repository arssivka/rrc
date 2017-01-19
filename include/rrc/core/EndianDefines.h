/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once

#include <cstdint>
#include "LittleEndian.h"
#include "BigEndian.h"


#define CURRENT_BYTE_ORDER       (*(int *)"\x01\x02\x03\x04")
#define LITTLE_ENDIAN_BYTE_ORDER 0x04030201
#define BIG_ENDIAN_BYTE_ORDER    0x01020304
#define PDP_ENDIAN_BYTE_ORDER    0x02010403

#define IS_LITTLE_ENDIAN (CURRENT_BYTE_ORDER == LITTLE_ENDIAN_BYTE_ORDER)
#define IS_BIG_ENDIAN    (CURRENT_BYTE_ORDER == BIG_ENDIAN_BYTE_ORDER)
#define IS_PDP_ENDIAN    (CURRENT_BYTE_ORDER == PDP_ENDIAN_BYTE_ORDER)


namespace rrc {
    using i8 = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;

    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

#if IS_BIG_ENDIAN

    using i16le = LittleEndian<i16> ;
    using i32le = LittleEndian<i32>;
    using i64le = LittleEndian<i64>;

    using u16le = LittleEndian<u16>;
    using u32le = LittleEndian<u32>;
    using u64le = LittleEndian<u64>;

    using i16be = i16;
    using i32be = i32;
    using i64be = i64;

    using u16be = u16;
    using u32be = u32;
    using u64be = u64;

#elif IS_LITTLE_ENDIAN

    using i16le = i16;
    using i32le = i32;
    using i64le = i64;

    using u16le = u16;
    using u32le = u32;
    using u64le = u64;

    using i16be = BigEndian<i16>;
    using i32be = BigEndian<i32>;
    using i64be = BigEndian<i64>;

    using u16be = BigEndian<u16>;
    using u32be = BigEndian<u32>;
    using u64be = BigEndian<u64>;

#elif IS_PDP_ENDIAN
#error PDP endianes aren't supported
#else
#error Unknown architecture
#endif

};