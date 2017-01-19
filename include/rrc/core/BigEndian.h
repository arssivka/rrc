/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    template<typename T> struct LittleEndian;

#pragma pack(push,1)

    template<typename T>
    struct BigEndian {
        union {
            unsigned char bytes[sizeof(T)];
            T raw_value;
        };

        BigEndian(T t = T()) {
            operator=(t);
        }

        BigEndian(const BigEndian<T>& t) {
            raw_value = t.raw_value;
        }

        BigEndian(const LittleEndian <T>& t) {
            for (unsigned i = 0; i < sizeof(T); i++)
                bytes[i] = t.bytes[sizeof(T) - 1 - i];
        }

        operator const T() const {
            T t = T();
            for (unsigned i = 0; i < sizeof(T); i++)
                t |= T(bytes[sizeof(T) - 1 - i]) << (i << 3);
            return t;
        }

        const T operator=(const T t) {
            for (unsigned i = 0; i < sizeof(T); i++)
                bytes[sizeof(T) - 1 - i] = t >> (i << 3);
            return t;
        }

        // operators

        const T operator+=(const T t) {
            return (*this = *this + t);
        }

        const T operator-=(const T t) {
            return (*this = *this - t);
        }

        const T operator*=(const T t) {
            return (*this = *this * t);
        }

        const T operator/=(const T t) {
            return (*this = *this / t);
        }

        const T operator%=(const T t) {
            return (*this = *this % t);
        }

        BigEndian<T> operator++(int) {
            BigEndian<T> tmp(*this);
            operator++();
            return tmp;
        }

        BigEndian<T>& operator++() {
            for (unsigned i = 0; i < sizeof(T); i++) {
                ++bytes[sizeof(T) - 1 - i];
                if (bytes[sizeof(T) - 1 - i] != 0)
                    break;
            }
            return (*this);
        }

        BigEndian<T> operator--(int) {
            BigEndian<T> tmp(*this);
            operator--();
            return tmp;
        }

        BigEndian<T>& operator--() {
            for (unsigned i = 0; i < sizeof(T); i++) {
                --bytes[sizeof(T) - 1 - i];
                if (bytes[sizeof(T) - 1 - i] != (T) (-1))
                    break;
            }
            return (*this);
        }
    };

#pragma pack(pop)
}
