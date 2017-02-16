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
            typedef typename detail::PropertyValueTraits<T>::VariantType VariantType;
            switch (Value::which<VariantType>()) {
                case Value::which<Nil>(): return PropertyType::Nil;
                case Value::which<Boolean>() : return PropertyType::Boolean;
                case Value::which<Number>() : return PropertyType::Number;
                case Value::which<String>() : return PropertyType::String;
                case Value::which<mapbox::util::recursive_wrapper<Array>>() : return PropertyType::Array;
                case Value::which<mapbox::util::recursive_wrapper<Table>>() : return PropertyType::Table;
                default: return PropertyType::Unknown;
            }
        }

        PropertyType getType() const;

        bool tryGetNumber(Number& outputNumber) const;

        bool tryGetBoolean(Boolean& outputBoolean) const;

        bool tryGetString(String& outputString) const;

        bool tryGetArray(Array& outputArray) const;

        bool tryGetTable(Table& outputTable) const;

        void setNil();

        void setBoolean(Boolean&& boolean);

        void setNumber(Number&& number);

        void setString(String&& string);

        void setArray(Array&& array);

        void setTable(Table&& table);

        void setBoolean(const Boolean& boolean);

        void setNumber(const Number& number);

        void setString(const String& string);

        void setArray(const Array& array);

        void setTable(const Table& table);

        bool isValid() const;

        bool isNil() const;

        bool isBoolean() const;

        bool isNumber() const;

        bool isString() const;

        bool isArray() const;

        bool isTable() const;

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