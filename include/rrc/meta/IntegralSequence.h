/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    namespace meta {
        /**
         * @brief Just a sequence of integral numbers
         * Example of using: IntegralSequence<int, 1, 2, 3>
         * @tparam T Type of the values to keep
         * @tparam Vals Values to keep
         */
        template<class T, T... Vals>
        class IntegralSequence {};
    }
}