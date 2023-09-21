#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <concepts>
#include <type_traits>

namespace hx::traits {

template<typename From, typename To>
concept NumericallyConvertible =
    std::is_arithmetic_v<To> && std::is_arithmetic_v<From> &&
    std::convertible_to<From, To>;

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
