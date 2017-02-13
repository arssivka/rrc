/**
 *  @autor arssivka
 *  @date 2/9/17
 */

#pragma once


namespace rrc {
    enum class PropertyType : int {
        Nil,
        Boolean,
        Number,
        String,
        Array,
        Table,
        Unknown
    };
}