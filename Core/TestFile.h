//
// Created by Michael Ferents on 25/07/2023.
//

#ifndef WUU_TESTFILE_H
#define WUU_TESTFILE_H

#include <ranges>
#include <coroutine>
#include <numbers>
#include <__numeric/midpoint.h>
#include "Graphics/Vulkan/Logger.h"

// coroutines are stackless - their state is allocated on the heap
/*
int range(int start, int end)
{
    while (start < end)
    {
        co_yield start;
        start++;
    }

    co_return;
}
*/
// concepts
/*
template <typename T>
concept always_satisfied = true;

template <typename T>
concept integral = std::is_integral_v<T>;

template <typename T>
concept signed_integral = integral<T> && std::is_signed_v<T>;

template <typename T>
concept unsigned_integral = integral<T> && !signed_integral<T>;

// enforcing concepts

template <integral T>
void f(T v);

template <typename T>
  requires integral<T>
void f(T v);

template <typename T>
void f(T v) requires integral<T>;

void f(integral auto v);

template <integral auto v>
void g();

template <typename T>
concept callable = requires (T f) { f(); };

template <typename T>
requires requires (T x) { x + x; }
T add(T a, T b)
{
    return a + b;
}

// Forms for auto-deduced variables:
// 'foo' is a constrained auto-deduced value;
integral auto foo = 5;

// lambda versions
auto s = []<integral T> (T v) {

};

auto j = []<typename T> requires integral<T> (T v) {

};

auto k = []<typename T> (T v) requires integral<T> {

};

auto l = [](integral auto v) {

};

auto d = []<integral auto v> () {

};
*/
// Type requirements
/*
struct foo {
    int foo;
};

struct bar {
    using value = int;
    value data;
};

struct baz {
    using value = int;
    value data;
};

// Using SFINAE, enable if 'T' is a 'baz'.
template <typename T, typename = std::enable_if_t<std::is_same_v<T, baz>>>
struct S {};

template <typename T>
using Ref = T&;

template <typename T>
concept C = requires {
    // Requirements on type 'T':
    typename T::value; // A) has an inner member named 'value'
    typename S<T>; // B) must have a valid class template specialization for 'S'
    typename Ref<T>; // c) must be a valid alias template substitution
};

template <C T>
void g(T a)
{
    std::cout << "Test" << std::endl;
}
*/
// Compund requirements
template <typename T>
concept C = requires(T x)
{
    {*x} -> std::convertible_to<typename T::inner>; // the type of the expression '*x' is convertible
    // to 'T::inner'
    {x + 1} -> std::same_as<int>; // the expression 'x + 1' satisfies 'std::same_as<decltype((x+1))>'
    {x * 1} -> std::convertible_to<T>; // the type of the expression 'x * 1' is convertible to 'T'
};
/*
// Nested requirements
template <typename T>
concept C = requires(T x) {
    requires std::same_as<sizeof(x), std::size_t>;
};
*/

// Designated initializers
struct A {
    int x;
    int y;
    int z = 123;
};

//A a { .x = 1, .z = 2};

// Template syntax for lambdas
/*
 * auto f = []<typename T>(std::vector<T> v) {
 * };
 *
 */

// [[likely]] and [[unlikely]] can also be used in if and while not just switch

// Class types in non-type template parameters (not sure what is going on here)
/*
struct Hoo {
    Hoo() = default;
    constexpr Hoo(int) {}
};

template <Hoo h>
auto getHoo()
{
    return h;
}

 getHoo(); // uses implicit constructor
 getHoo<Hoo{123}>();

 */

// constexpr virtual functions
/*
struct X1 {
    virtual int f() const = 0;
};

struct X2 : public X1 {
    constexpr virtual int f() const { return 2; }
};

struct X3 : public X2 {
    virtual int f() const { return 3; }
};

struct X4 : public X3 {
    constexpr virtual int f() const { return 4; }
};

constexpr X4 x4;
x4.f(); // == 4
*/

// explicit(bool) - conditionally select at compile-time whther a constructor is made explicit or not.
/*
struct foo {
    template <typename T>
    explicit(!std::is_integral_v<T>) foo(T) {}
};

 foo a = 123; // ok
 foo b = "123"; // Error: explicit constructor is not a candidate (explicit specifier evaluates to true)
 foo c {"123"}; // ok

*/
// Immediate functions
/*
consteval int sqr(int n) {
    return n * n;
}

 constexpr int r = sqr(100); // OK
 int x = 100;
 int r2 =  sqr(x); Error: the value of 'x' is not usable in a constant expression - OK if 'sqr' were a 'constexpr' function

 */

// "using enum" - eg
enum class rgba_color_channel { red, green, blue, alpha };

static std::string_view to_string(rgba_color_channel my_channel)
{
    switch(my_channel)
    {
        using enum rgba_color_channel;
        case red: return "red";
        case green: return "green";
        case blue: return "blue";
        case alpha: return "alpha";
    }
}

// "constinit" - constinit specifier requires that a varibale must be initialized at compile-time
static const char* g() { return "dynamic initialization"; }
constexpr const char* f(bool p) { return p ? "constant initializer" : g(); }

//constinit const char* c = f(true); // OK
//constinit const char* d = f(false); // Error: 'g' is not constexpr, so 'd' cannot be evaluated at compile-time

// std::span - view (non-owning) of a containor providing bounds-checked access to a contiguous group of
// elements - cheap to construct and copy
static void print_ints(std::span<const int> ints)
{
    for(const auto n : ints)
    {
        std::cout << n << std::endl;
    }
}

// Math constants
//float pi = std::numbers::pi;
//float euler = std::numbers::e;

// std::is_constant_evaluated - Predicate function which is truthy when it is called in a compile-time context
constexpr bool is_compile_time()
{
    return std::is_constant_evaluated();
}

constexpr bool m = is_compile_time(); //true
// bool s = is_compile_time(); False

// Automatic template argument deduction much like how it's done for functions, but now including constructors.
template <typename T = float>
struct MyContainer {
    T val;
    MyContainer() : val{} {}
    MyContainer(T val) : val{val} {}
};

//MyContainer c1 { 1 }; // OK MyContainer<int>
//MyContainer c2; // OK MyContainer<float>

// Declaring non-type template parameters with auto
template <auto... seq>
struct my_integer_sequence {

};

// Explicitly pass type 'int' as template argument.
//auto seq = std::integer_sequence<int, 0, 1, 2>();
// Type is deduced to be 'int'.
//auto seq2 = my_integer_sequence<0, 1, 2>();

// Folding expressions
template <typename... Args>
bool logicalAnd(Args... args)
{
    // Binary folding.
    return (true && ... && args);
}
/*
 *
 * bool b = true;
 * bool& b2 = b;
 * logicalAnd(b,b2,true); // == true
 *
 */
template <typename... Args>
auto sum(Args... args)
{
    // Unary folding.
    return (... + args);
}

// sum(1.0, 2.0f, 3); // == 6.0

// New rules for auto deduction from braced-init-list
// auto x1 {1, 2, 3}; // error: not a single element
//auto x2 = { 1, 2, 3}; // x2 is std::initializer_list<int>
//auto x3 {3}; // x3 is int
//auto x4 {3.0}; // x4 is double

// Compile-time lambdas using constexpr
auto identity = [](int n) constexpr { return n; };
static_assert(identity(123) == 123);

struct MyObj {
    int value {123};
    auto getValueCopy() {
        return [*this] { return value; };
    }
    auto getValueRef() {
        return [this] { return value; };
    }
};
/*
MyObj mo;
auto valueCopy = mo.getValueCopy();
auto valueRef = mo.getValueRef();
mo.value = 321;
valueCopy(); // 123
valueRef(); // 321
*/

// constexpr if
template <typename T>
constexpr bool isIntegral() {
    if constexpr (std::is_integral<T>::value)
    {
        return true;
    } else {
        return false;
    }
}

// std::variant - holds a value of one of its alternative types
// std::optional - a value that may or may not be present

// std::invoke
/*
template<typename Callable>
class Proxy {
   Callable c_;

public:

        Proxy(Callable c) : c_{ std::move(c) } {}

        template<typename... Args>
        decltype(auto) operator()(Args&&... args)
        {
            // ...
            return std::invoke(c_, std::forward<Args>(args)...);
        }

};

 const auto add = [](int x, int y) { return x + y; };
 Proxy p{ add };
 p(1,2); // == 3

 */

// std::apply
auto add = [](int x, int y) {
    return x + y;
};

//std::apply(add, std::make_tuple(1, 2)); // == 3

// Generic lambda expressions

//auto identitys = [](auto x) { return x; };
//int three = identitys(3); // == 3
//std::string foo = identitys("foo"); // == "foo"
/*
// decltype(auto) - it deduces return types while keeping their references and cv-qualifiers, while auto will not
const int x = 0;
auto a1 = x; // int
decltype(auto) a2 = x; // const int
int y = 0;
int& b1 = y;
auto b2 = b1; // int
decltype(auto) b3 = b1; // int&
int&& z = 0;
auto g1 = std::move(z);
decltype(auto) g2 = std::move(z); // int&&
*/
// constexpr - constant expressions are expressions that are possibly evaluated by the compiler at compile-time
constexpr int square(int x)
{
    return x * x;
}
/*
// User-defined literals

// Converting Celsius to Fahrenheit
// 'unsigned long long' parameter required for integer literal.
long long operator "" _celsius(unsigned long long tempCelsius)
{
    return std::llround(tempCelsius * 1.8 + 32);
}

float fahrenheit = 24_celsius;

// String to integer conversion
// 'const char*' and 'std::size_t' required as parameters.
int operator "" _int(const char* str, std::size_t)
{
    return std::stoi(str);
}

int test = "123"_int;

// conversion / explicit conversion functions
struct J {
    operator bool() const { return true; }

};

struct N {
    explicit operator bool() const { return true; }
};

J j;
//if (j);  // OK calls J::operator bool()
bool ba = j; // OK copy-initialization selects J::operator bool()

N n;
//if(n); // OK calls N::operator bool()
// bool bb = n; error copy-initialization does not consider N::operator bool()
*/

struct Event {

    explicit Event(std::string_view message) : event(message) {}

    std::string event;

    [[nodiscard]] std::string_view to_string() const
    {
        return event;
    }
};

static void testmain()
{
    //g(baz{});
    // Range-based for loop with initializer
    /*
    for(auto v = std::vector{1, 2, 3}; auto& e : v)
    {
        std::cout << e;
    }
     */
    //print_ints(std::vector{ 1, 2, 3});
    //print_ints(std::array<int, 5>{ 1, 2, 3, 4, 5});

    std::string str = "foobar";
    str.starts_with("foo"); // true
    str.ends_with("baz"); // false

    // std::midpoint
    std::midpoint(1, 3); // == 2

    Logger<Event> eventLogger {};

    eventLogger.log(Event("First LOG"));
    eventLogger.log(Event("Second LOG"));
    eventLogger.log(Event("Third LOG"));

    eventLogger.print();
}


#endif //WUU_TESTFILE_H
