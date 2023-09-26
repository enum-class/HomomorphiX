#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <concepts>
#include <type_traits>

namespace hx::traits {

__extension__ typedef __int128 int128_t;
__extension__ typedef unsigned __int128 uint128_t;

template<typename t>
inline constexpr bool is_uc = sizeof(unsigned char) == sizeof(t) && std::is_unsigned_v<t>;

template<typename t>
inline constexpr bool is_us = sizeof(unsigned short int) == sizeof(t) && std::is_unsigned_v<t>;

template<typename t>
inline constexpr bool is_u = sizeof(unsigned int) == sizeof(t) && std::is_unsigned_v<t>;

template<typename T>
inline constexpr bool is_ul = sizeof(unsigned long int) == sizeof(T) && std::is_unsigned_v<T>;

template<typename T>
inline constexpr bool is_ull = sizeof(unsigned long long int) == sizeof(T) && std::is_unsigned_v<T>;

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept Unsigned = std::is_unsigned_v<T>;

template<typename T>
concept Float = std::is_floating_point_v<T>;

template<typename From, typename To>
concept NumericallyConvertible =
    std::is_arithmetic_v<To> && std::is_arithmetic_v<From> && std::convertible_to<From, To>;

template<typename From, typename To, typename = void>
struct is_narrowing_impl : std::true_type {};

template<typename From, typename To>
struct is_narrowing_impl<From, To,
                         std::void_t<decltype(To{ std::declval<From>() })>>
    : std::false_type {};

template<typename From, typename To>
  requires NumericallyConvertible<From, To>
struct is_narrowing : is_narrowing_impl<From, To> {};

template<class From, class To>
inline constexpr bool is_narrowing_v = is_narrowing<From, To>::value;

}  // namespace hx::traits
#endif
