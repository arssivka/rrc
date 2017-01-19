/**
 *  @autor arssivka
 *  @date 1/19/17
 */

#pragma once


namespace rrc {
    template<typename T> struct BigEndian;

#pragma pack(push,1)

    template<typename T>
    struct LittleEndian {
        union {
            unsigned char bytes[sizeof(T)];
            T raw_value;
        };

        LittleEndian(T t = T()) {
            operator=(t);
        }

        LittleEndian(const LittleEndian<T>& t) {
            raw_value = t.raw_value;
        }

        LittleEndian(const BigEndian<T>& t) {
            for (unsigned i = 0; i < sizeof(T); i++)
                bytes[i] = t.bytes[sizeof(T) - 1 - i];
        }

        operator const T() const {
            T t = T();
            for (unsigned i = 0; i < sizeof(T); i++)
                t |= T(bytes[i]) << (i << 3);
            return t;
        }

        const T operator=(const T t) {
            for (unsigned i = 0; i < sizeof(T); i++)
                bytes[i] = t >> (i << 3);
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

        LittleEndian<T> operator++(int) {
            LittleEndian<T> tmp(*this);
            operator++();
            return tmp;
        }

        LittleEndian<T>& operator++() {
            for (unsigned i = 0; i < sizeof(T); i++) {
                ++bytes[i];
                if (bytes[i] != 0)
                    break;
            }
            return (*this);
        }

        LittleEndian<T> operator--(int) {
            LittleEndian<T> tmp(*this);
            operator--();
            return tmp;
        }

        LittleEndian<T>& operator--() {
            for (unsigned i = 0; i < sizeof(T); i++) {
                --bytes[i];
                if (bytes[i] != (T) (-1))
                    break;
            }
            return (*this);
        }
    };

#pragma pack(pop)
}