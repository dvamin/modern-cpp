#include <iostream>
#include <type_traits>

template <bool B, typename T = void>
struct enable_if;

template <typename T>
struct enable_if<true, T> { using type = T; };

template <typename T, typename U>
struct is_same_type : std::false_type {};

template <typename T>
struct is_same_type<T, T> : std::true_type {};

struct foo {
    int get() { return 4; }
};

struct bar {
    int get_() { return 4; }
};

template <typename T>
struct has_get {
    template <typename U>
    static constexpr decltype(U().get()) f(int) { return 0; }

    template <typename U>
    static constexpr void f(...) { }

    static constexpr bool value = is_same_type<decltype(f<T>(0)), int>::value;
};

int main()
{
    std::cout << has_get<foo>::value << std::endl;
    std::cout << has_get<bar>::value << std::endl;
}
