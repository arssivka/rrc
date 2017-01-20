/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <cstdint>
#include <cstddef>

namespace rrc {
    namespace detail {
        class IterationTag { };
        class FinalIterationTag : public IterationTag { };

        template <size_t N>
        class IterationTraits {
        public:
            using Tag = IterationTag;
        };

        template<>
        class IterationTraits<0> {
        public:
            using Tag = FinalIterationTag;
        };
    }

    class Varint {
    private:

        template<class Value, size_t N = sizeof(Value) + 1>
        inline static size_t encodeImplementation(Value value, uint8_t* output, detail::IterationTag) {
            using Tag = typename detail::IterationTraits<N - 1>::Tag;
            return (value > 127)
                   ? (output[sizeof(Value) + 1 - N] = ((uint8_t) (value & 127) | 128), Varint::encodeImplementation<Value, N - 1>(value >> 7, output, Tag()))
                   : (output[sizeof(Value) + 1 - N] = ((uint8_t) value & 127), sizeof(Value) + 2 - N);
        };

        template<class Value, size_t N>
        inline static size_t encodeImplementation(Value value, uint8_t* output, detail::FinalIterationTag) {
            return (output[sizeof(Value) + 1] = ((uint8_t) value & 127), sizeof(Value) + 1);
        };

        template<class Value, size_t N = sizeof(Value) + 1>
        inline static Value decodeImplementation(uint8_t* input, Value acc, detail::IterationTag) {
            using Tag = typename detail::IterationTraits<N - 1>::Tag;
            return ((input[sizeof(Value) - N + 1] & 128))
                   ? Varint::decodeImplementation<Value, N - 1>(input, acc | (input[sizeof(Value) + 1 - N] & 127) << (7 * (sizeof(Value) + 1 - N)), Tag())
                   : acc | (input[sizeof(Value) + 1 - N] & 127) << (7 * (sizeof(Value) + 1 - N));
        };

        template<class Value, size_t N>
        inline static Value decodeImplementation(uint8_t* input, Value acc, detail::FinalIterationTag) {
            return acc | (input[sizeof(Value) + 1] & 127) << (7 * (sizeof(Value) + 1));
        };

    public:
        template<class Value = uint64_t>
        static size_t encode(Value value, uint8_t* output) {
            return Varint::encodeImplementation(value, output, detail::IterationTag());
        }

        template<class Value = uint64_t>
        static Value decode(uint8_t* input) {
            return Varint::decodeImplementation(input, 0, detail::IterationTag());
        }


    };
}