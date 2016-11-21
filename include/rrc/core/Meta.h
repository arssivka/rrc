/**
 *  @autor arssivka
 *  @date 11/15/16
 */

#pragma once


#include <functional>

namespace rrc {
    template<typename T>
    struct FunctionTraits;

    template<typename Res, typename ...Args>
    struct FunctionTraits<std::function<Res(Args...)>> {
        static const size_t count = sizeof...(Args);

        using Result = Res;

        template<size_t i>
        using Arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };

    template<typename Res, typename ...Args>
    struct FunctionTraits<Res(*)(Args...)> {
        static const size_t count = sizeof...(Args);

        using Result = Res;

        template<size_t i>
        using Arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };

    template<typename T>
    struct MethodTraits;

    template<typename Res, typename Cls, typename ...Args>
    struct MethodTraits<Res(Cls::*)(Args...)> {
        static const size_t count = sizeof...(Args);

        using Result = Res;

        using Class = Cls;

        template<size_t i>
        using Ars = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
}