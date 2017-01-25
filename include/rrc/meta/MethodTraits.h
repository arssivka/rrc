/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <cstddef>

namespace rrc {
    /**
     * @brief Gives all the information about specified method.
     * You can recieve type of any argument. Returning type. Quantity of arguments.
     * Example of using: MethodTraits<decltype(&SomeClass::SomeFunc>::Arg<0>
     * FunctionTraits<decltype(&SomeClass::SomeFunc>::Arg<1>
     * FunctionTraits<decltype(&SomeClass::SomeFunc>::Result
     * FunctionTraits<decltype(&SomeClass::SomeFunc>::count
     * @tparam T Needed method to extract traits.
     */
    template<typename T>
    class MethodTraits;

    template<typename Res, typename Cls, typename ...Args>
    class MethodTraits<Res(Cls::*)(Args...)> {
    public:
        static const size_t count = sizeof...(Args);
        using Result = Res;
        using Class = Cls;
        template<size_t i> using Arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
}