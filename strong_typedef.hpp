#pragma once

#include <type_traits>

namespace strong_typedef
{
    class _strong_typedef
    {
    };

    template <typename T, typename Tag>
    class type : _strong_typedef
    {
    public:
        using value_type = T;
        using tag_type = Tag;

        explicit type(const T &value) : _value(value) {}

        T &get() { return _value; }
        const T &get() const { return _value; }

        bool operator==(const type &rhs) const { return _value == rhs._value; }
        bool operator!=(const type &rhs) const { return _value != rhs._value; }

    private:
        T _value;
    };

    struct _operators_undefined
    {
    };

    template <typename T>
    concept _is_operators_defined = !std::is_same<T, _operators_undefined>::value;

    template <class In1, class In2 = void>
    struct operators
    {
        using add = _operators_undefined;
        using subtract = _operators_undefined;
        using multiply = _operators_undefined;
        using divide = _operators_undefined;
        using modulo = _operators_undefined;
        using equal = _operators_undefined;
        using not_equal = _operators_undefined;
        using less = _operators_undefined;
        using less_equal = _operators_undefined;
        using greater = _operators_undefined;
        using greater_equal = _operators_undefined;
        using logical_and = _operators_undefined;
        using logical_or = _operators_undefined;

        using plus = _operators_undefined;
        using minus = _operators_undefined;
        using logical_not = _operators_undefined;
    };

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::add>
    operators<In1, In2>::add operator+(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::add(lhs.get() + rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::subtract>
    operators<In1, In2>::subtract operator-(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::subtract(lhs.get() - rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::multiply>
    operators<In1, In2>::multiply operator*(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::multiply(lhs.get() * rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::divide>
    operators<In1, In2>::divide operator/(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::divide(lhs.get() / rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::modulo>
    operators<In1, In2>::modulo operator%(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::modulo(lhs.get() % rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::equal>
    operators<In1, In2>::equal operator==(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::equal(lhs.get() == rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::not_equal>
    operators<In1, In2>::not_equal operator!=(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::not_equal(lhs.get() != rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::less>
    operators<In1, In2>::less operator<(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::less(lhs.get() < rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::less_equal>
    operators<In1, In2>::less_equal operator<=(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::less_equal(lhs.get() <= rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::greater>
    operators<In1, In2>::greater operator>(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::greater(lhs.get() > rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::greater_equal>
    operators<In1, In2>::greater_equal operator>=(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::greater_equal(lhs.get() >= rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::logical_and>
    operators<In1, In2>::logical_and operator&&(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::logical_and(lhs.get() && rhs.get());
    }

    template <class In1, class In2>
        requires _is_operators_defined<typename operators<In1, In2>::logical_or>
    operators<In1, In2>::logical_or operator||(const In1 &lhs, const In2 &rhs)
    {
        return typename operators<In1, In2>::logical_or(lhs.get() || rhs.get());
    }

    template <class In>
        requires _is_operators_defined<typename operators<In>::plus>
    operators<In>::plus operator+(const In &lhs)
    {
        return typename operators<In>::plus(+lhs.get());
    }

    template <class In>
        requires _is_operators_defined<typename operators<In>::minus>
    operators<In>::minus operator-(const In &lhs)
    {
        return typename operators<In>::minus(-lhs.get());
    }

    template <class In>
        requires _is_operators_defined<typename operators<In>::logical_not>
    operators<In>::logical_not operator!(const In &lhs)
    {
        return typename operators<In>::logical_not(!lhs.get());
    }
}