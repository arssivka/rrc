/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


#include <cstdint>
#include <cstddef>

namespace rrc {
    class Varint {
    public:
        template<class Value = uint64_t>
        static size_t encode(Value value, uint8_t* output) {
            return Varint::encodeImplementation(value, output);
        }

        template<class Value = uint64_t>
        static Value decode(uint8_t* input) {
            return Varint::decodeImplementation(input);
        }

    private:
        template<class Value, size_t N = sizeof(Value) + 1>
        inline static size_t encodeImplementation(Value value, uint8_t* output) {
            return (value > 127)
                   ? (output[sizeof(Value) - N + 1] = (uint8_t) (value & 127) | 128, Varint::encodeImplementation<Value, N - 1>(value >> 7, output))
                   : (output[sizeof(Value) - N + 1] = (uint8_t) value & 127, sizeof(Value) - N + 1);
        };

        template<class Value>
        inline static size_t encodeImplementation<Value, 0>(Value value, uint8_t* output) {
            return (output[sizeof(Value)] = ((uint8_t)value) & 127, sizeof(Value) + 1);
        };

        template<class Value, size_t N = sizeof(Value) + 1>
        inline static Value decodeImplementation(uint8_t* input, Value acc = 0) {
            return ((input[sizeof(Value) - N + 1] & 128))
                   ? Varint::decodeImplementation<Value, N - 1>(input, acc | (input[sizeof(Value) - N + 1] & 127) << (7 * sizeof(Value) - N + 1))
                   : acc | (input[sizeof(Value) - N + 1] & 127) << (7 * sizeof(Value) - N);
        };

        template<class Value>
        inline static Value decodeImplementation<Value, 0>(uint8_t* input, Value acc) {
            return acc | (input[sizeof(Value) + 1] & 127) << (7 * sizeof(Value));
        };
    };
}