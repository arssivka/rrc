/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include "rrc/meta.h"

namespace rrc {

    class Varint {
    private:

        template<class Value, size_t N = sizeof(Value) + 1>
        inline static size_t encodeImplementation(Value value, uint8_t* output, meta::IterationTag) {
            using Tag = meta::IterationTraits<N - 1>;
            return (value > 127)
                   ? (output[sizeof(Value) + 1 - N] = ((uint8_t) (value & 127) | 128), Varint::encodeImplementation<Value, N - 1>(value >> 7, output, Tag()))
                   : (output[sizeof(Value) + 1 - N] = ((uint8_t) value & 127), sizeof(Value) + 2 - N);
        };

        template<class Value, size_t N>
        inline static size_t encodeImplementation(Value value, uint8_t* output, meta::FinalIterationTag) {
            return (output[sizeof(Value) + 1] = ((uint8_t) value & 127), sizeof(Value) + 1);
        };

        template<class Value, size_t N = sizeof(Value) + 1>
        inline static Value decodeImplementation(uint8_t* input, Value acc, meta::IterationTag) {
            using Tag = meta::IterationTraits<N - 1>;
            return ((input[sizeof(Value) - N + 1] & 128))
                   ? Varint::decodeImplementation<Value, N - 1>(input, acc | (input[sizeof(Value) + 1 - N] & 127) << (7 * (sizeof(Value) + 1 - N)), Tag())
                   : acc | (input[sizeof(Value) + 1 - N] & 127) << (7 * (sizeof(Value) + 1 - N));
        };

        template<class Value, size_t N>
        inline static Value decodeImplementation(uint8_t* input, Value acc, meta::FinalIterationTag) {
            return acc | (input[sizeof(Value) + 1] & 127) << (7 * (sizeof(Value) + 1));
        };

    public:
        template<class Value = uint64_t>
        static size_t encode(Value value, uint8_t* output) {
            return Varint::encodeImplementation(value, output, meta::IterationTag());
        }

        template<class Value = uint64_t>
        static Value decode(uint8_t* input) {
            return Varint::decodeImplementation(input, 0, meta::IterationTag());
        }
    };
}