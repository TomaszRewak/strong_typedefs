#include "strong_typedef.hpp"

using price = strong_typedef::type<double, struct price_tag>;
using quantity = strong_typedef::type<int, struct quantity_tag>;

template <>
struct strong_typedef::operators<price, price>
{
    using add = price;
    using subtract = price;
};

template <>
struct strong_typedef::operators<price, quantity>
{
    using multiply = price;
    using divide = price;
};

template <>
struct strong_typedef::operators<price>
{
    using minus = price;
};

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

    use(v, p);     // Compile-time error
    use(p + v, v); // Compile-time error
    use(1, 3);     // Compile-time error
}