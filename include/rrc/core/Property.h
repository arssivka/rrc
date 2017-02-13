/**
 *  @autor tekatod
 *  @date 7/15/16
 */
#pragma once


#include <ostream>
#include "mapbox/variant.hpp"
#include "mapbox/recursive_wrapper.hpp"
#include "CopyOnWrite.h"
#include "PropertyType.h"
#include "Nil.h"
#include "Boolean.h"
#include "Number.h"
#include "String.h"
//#include "Array.h"
//#include "Table.h"


namespace rrc {
    class Array;
    class Table;

    namespace detail {
        template <class T>
        struct PropertyValueTraits {
            typedef T VariantType;
        };

        template <>
        struct PropertyValueTraits<Array> {
            typedef mapbox::util::recursive_wrapper<Array> VariantType;
        };

        template <>
        struct PropertyValueTraits<Table> {
            typedef mapbox::util::recursive_wrapper<Table> VariantType;
        };
    }
    /**
     * @brief Property is a class for holding and modifying the setting of the node. It can hold float, bool, int or string.
     */
    class Property {
    private:
        typedef mapbox::util::variant<Nil, Boolean, Number, String,
                                mapbox::util::recursive_wrapper<Array>,
                                mapbox::util::recursive_wrapper<Table>> Value;

    public:
        Property(const String& string);

        Property(String&& string);

        Property(const Number& number);

        Property(Number&& number);

        Property(const Boolean& boolean);

        Property(Boolean&& boolean);

        Property(const Array& array);

        Property(Array&& array);

        Property(const Table& table);

        Property(Table&& table);

        /**
         * @brief Copy constructor of property
         * @param other Other const property instance to copy from
         */
        Property(const Property& other) = default;

        /**
         * @brief Move constructor of property
         * @param other Other property instance to move from
         */
        Property(Property&& other) = default;

        /**
         * @brief Default property constructor
         */
        Property();

        /**
         * @brief Default = Operator of property
         * @param other Const reference to Property instance
         * @return Property&
         */
        Property& operator=(const Property& other) = default;

        /**
         * @brief Default = Operator of property
         * @param other Rvalue reference to Property instance
         * @return Property&
         */
        Property& operator=(Property&& other) = default;

        template <class T>
        static PropertyType getType() {
            switch (Value::which<detail::PropertyValueTraits<T>::VariantType>()) {
                case Value::which<Nil>(): return PropertyType::Nil;
                case Value::which<Boolean>() : return PropertyType::Boolean;
                case Value::which<Number>() : return PropertyType::Number;
                case Value::which<String>() : return PropertyType::String;
                case Value::which<mapbox::util::recursive_wrapper<Array>>() : return PropertyType::Array;
                case Value::which<mapbox::util::recursive_wrapper<Table>>() : return PropertyType::Table;
                default: return PropertyType::Unknown;
            }
        }

        inline PropertyType getType() const;

        inline bool tryGetNumber(Number& outputNumber) const;

        inline bool tryGetBoolean(Boolean& outputBoolean) const;

        inline bool tryGetString(String& outputString) const;

        inline bool tryGetArray(Array& outputArray) const;

        inline bool tryGetTable(Table& outputTable) const;

        inline void setNil();

        inline void setBoolean(Boolean&& boolean);

        inline void setNumber(Number&& number);

        inline void setString(String&& string);

        inline void setArray(Array&& array);

        inline void setTable(Table&& table);

        inline bool isValid() const;

        inline bool isNil() const;

        inline bool isBoolean() const;

        inline bool isNumber() const;

        inline bool isString() const;

        inline bool isArray() const;

        inline bool isTable() const;

        bool operator==(const Property& rhs) const;

        bool operator!=(const Property& rhs) const;

        bool operator<(const Property& rhs) const;

        bool operator>(const Property& rhs) const;

        bool operator<=(const Property& rhs) const;

        bool operator>=(const Property& rhs) const;

        friend std::ostream& operator<<(std::ostream& os, const rrc::Property& property);

    private:
        CopyOnWrite<Value> mValue;

    };
}