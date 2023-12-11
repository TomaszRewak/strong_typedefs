## About

A (yet another) `strong_typedef` implementation for C++.

`strong_typedef`s allow you to create new types that are derived from existing ones, but are not implicitly convertible to them. This allows you to create types that are semantically different, but have the same underlying representation.

Using `strong_typedef`s helps in avoiding some common pitfalls, like accidentally adding a distance to a time or passing a weight to a function that expects a price (where all of could be represented by a `double`).

This (single-header) library also provides a convenient way of defining common operators for your new types. You can express that it makes sense to multiply a price by a quantity, while preventing the multiplication of two prices.

## Usage

Include the header file:

```cpp
#include "strong_typedef.hpp"
```

Define your new types:

```cpp
using price = strong_typedef::type<double, struct price_tag>;
using quantity = strong_typedef::type<int, struct quantity_tag>;
```

Express which operations are allowed and what are their result types:

```cpp
template <>
struct strong_typedef::operators<price, price>    // price □ price
{
    using add = price;                            // price + price => price
    using subtract = price;                       // price - price => price
};

template <>
struct strong_typedef::operators<price, quantity> // price □ quantity
{
    using multiply = price;                       // price * quantity => price
    using divide = price;                         // price / quantity => price
};

template <>
struct strong_typedef::operators<price>           // □ price
{
    using minus = price;                          // - price => price
};
```

You can now use your new types:

```cpp
void use(price price, quantity quantity) { /**/ }

int main()
{
    price p{1.0};
    quantity v{3};

    use(p, v);                           // OK
    use(p * v, v);                       // OK
    use(-p, v);                          // OK
    use(price{1}, quantity{3});          // OK
    use(p, quantity{p.get() + v.get()}); // OK, on your own risk

    use(v, p);     // Compile-time error (cannot pass a price as a quantity and vice versa)
    use(p + v, v); // Compile-time error (cannot add quantity to a price)
    use(1, 3);     // Compile-time error (cannot implicitly convert between a number and price/quantity)
}
```

You can retrieve the internal value using the `get()` method:

```cpp
price p{1.0};

double d = p.get();
```

The list of supported operators is:

```cpp
template <class In1, class In2 = void>
struct strong_typedef::operators
{
    // For strong_typedef::operators<In1, In2>
    using add = _operator_undefined;
    using subtract = _operator_undefined;
    using multiply = _operator_undefined;
    using divide = _operator_undefined;
    using modulo = _operator_undefined;
    using equal = _operator_undefined;
    using not_equal = _operator_undefined;
    using less = _operator_undefined;
    using less_equal = _operator_undefined;
    using greater = _operator_undefined;
    using greater_equal = _operator_undefined;
    using logical_and = _operator_undefined;
    using logical_or = _operator_undefined;

    // For strong_typedef::operators<In1>
    using plus = _operator_undefined;
    using minus = _operator_undefined;
    using logical_not = _operator_undefined;
};
```
