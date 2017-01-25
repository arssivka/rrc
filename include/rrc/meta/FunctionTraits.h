/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <cstddef>
#include <functional>

namespace rrc {
    /**
     * @brief Gives all the information about specified function.
     * You can recieve type of any argument. Returning type. Quantity of arguments.
     * Example of using: FunctionTraits<std::function<void(float, int)>>::Arg<0>
     * FunctionTraits<std::function<void(float, int)>>::Arg<1>
     * FunctionTraits<std::function<void(float, int)>>::Result
     * FunctionTraits<std::function<void(float, int)>>::count
     * @tparam T Needed function to extract traits. Function pointer can be applied too.
     */
    template<typename T>
    class FunctionTraits;

    template<typename Res, typename ...Args>
    class FunctionTraits<std::function<Res(Args...)>> {
    public:
        static const size_t count = sizeof...(Args);
        using Result = Res;
        template<size_t i> using Arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };

    template<typename Res, typename ...Args>
    class FunctionTraits<Res(*)(Args...)> {
    public:
        static const size_t count = sizeof...(Args);
        using Result = Res;
        template<size_t i> using Arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
}