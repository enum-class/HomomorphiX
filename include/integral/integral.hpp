#ifndef INTEGRAL_HPP
#define INTEGRAL_HPP

#include <cstdint>
#include <limits>
#include <optional>

#include "traits/traits.hpp"
#include "xsimd/xsimd.hpp"

namespace hx::integral {

template<typename From, typename To>
  requires traits::NumericallyConvertible<From, To>
[[nodiscard]] inline constexpr bool is_value_fittable([[maybe_unused]] From from) noexcept {
  if constexpr (!traits::is_narrowing_v<From, To>) {
    return true;
  } else if constexpr (std::is_integral_v<To> && std::is_integral_v<From>) {
    if constexpr (std::is_signed_v<From> && std::is_unsigned_v<To>) {
      if (from >= 0)
        return static_cast<std::uint64_t>(from) <=
               static_cast<std::uint64_t>(std::numeric_limits<To>::max());
      else
        return false;
    } else {
      return from <= static_cast<From>(std::numeric_limits<To>::max());
    }

  } else if constexpr (std::is_floating_point_v<To> &&
                       std::is_floating_point_v<From>) {
    return from <= static_cast<From>(std::numeric_limits<To>::max()) &&
           from >= static_cast<From>(-std::numeric_limits<To>::max());
  } else if constexpr (std::is_integral_v<To> &&
                       std::is_floating_point_v<From>) {
    return from <= static_cast<From>(std::numeric_limits<To>::max()) &&
           from >= static_cast<From>(std::numeric_limits<To>::min());
  } else if constexpr (std::is_integral_v<From> &&
                       std::is_floating_point_v<To>) {
    return static_cast<To>(from) <= std::numeric_limits<To>::max() &&
           static_cast<To>(from) >= -std::numeric_limits<To>::max();
  }
}

template<typename To, typename From>
  requires traits::NumericallyConvertible<From, To>
[[nodiscard]] inline constexpr std::optional<To> secure_cast(From from) noexcept {
  if (is_value_fittable<From, To>(from)) return static_cast<To>(from);
  return std::nullopt;
}

template<traits::Integral T>
[[nodiscard]] inline constexpr std::optional<T> secure_mul(T a, T b) noexcept {
  if constexpr (__has_builtin(__builtin_mul_overflow)) {
    T result = 0;
    if (__builtin_mul_overflow(a, b, &result)) [[unlikely]]
      return std::nullopt;
    return result;
  } else {
    // TODO:
    return std::nullopt;
  }
}

template<traits::Integral T, traits::Integral... Args>
[[nodiscard]] inline constexpr T secure_mul(T in1, T in2, Args &&...args) {
  return secure_mul(secure_mul(in1, in2), secure_mul(std::forward<Args>(args)...));
}

template<traits::Integral T>
[[nodiscard]] inline constexpr std::optional<T> secure_add(T a, T b) noexcept {
  if constexpr (__has_builtin(__builtin_add_overflow)) {
    T result = 0;
    if (__builtin_add_overflow(a, b, &result)) [[unlikely]]
      return std::nullopt;
    return result;
  } else {
    // TODO:
    return std::nullopt;
  }
}

template<traits::Integral T, traits::Integral... Args>
[[nodiscard]] inline constexpr T secure_add(T in1, T in2, Args &&...args) noexcept {
  return secure_add(secure_add(in1, in2), secure_add(std::forward<Args>(args)...));
}

template<traits::Integral T> [[nodiscard]] inline constexpr T secure_inc(T a) noexcept {
  return secure_add(a, T{ 1 });
}

template<traits::Integral T>
[[nodiscard]] inline constexpr std::optional<T> secure_sub(T a, T b) noexcept {
  if constexpr (__has_builtin(__builtin_sub_overflow)) {
    T result = 0;
    if (__builtin_sub_overflow(a, b, &result)) [[unlikely]]
      return std::nullopt;
    return result;
  } else {
    // TODO:
    return std::nullopt;
  }
}

template<traits::Integral T> [[nodiscard]] inline constexpr T secure_dec(T a) noexcept {
  return secure_sub(a, T{ 1 });
}

template<traits::Float T> [[nodiscard]] inline constexpr bool near(T value1, T value2) noexcept {
  T scale_factor = std::max<T>({ std::fabs(value1), std::fabs(value2), T{ 1.0 } });
  return std::fabs(value1 - value2) < std::numeric_limits<T>::epsilon() * scale_factor;
}

template<traits::Integral T> inline constexpr bool is_power_of_two(T value) noexcept {
  return value && !(value & (value - 1));
}

template<traits::Integral T>
[[nodiscard]] inline constexpr std::optional<size_t> msb(T value) noexcept {
  // TODO: move to bitwise
  if (value == T{ 0 }) return std::nullopt;

  int (*operation)(T) = nullptr;

  if constexpr (traits::is_u<T> && __has_builtin(__builtin_clz))
    operation = __builtin_clz;
  else if constexpr (traits::is_ul<T> && __has_builtin(__builtin_clzl))
    operation = __builtin_clzl;
  else if constexpr (traits::is_ull<T> && __has_builtin(__builtin_clzll))
    operation = __builtin_clzll;
  else
    return std::nullopt;  // TODO:

  return (sizeof(T) - size_t{ 1 }) - safe_cast<size_t>(operation(value));
}

template<traits::Integral T>
[[nodiscard]] inline constexpr std::optional<size_t> exponent_of_power_two(T value) noexcept {
  if (is_power_of_two(value))
    if (auto idx = msb(value); idx) return secure_add(*idx, size_t{ 1 });

  return std::nullopt;
}

template<traits::Unsigned T>
[[nodiscard]] inline constexpr bool is_prime(T value) noexcept a
    // TODO:
    return false;
}

template<traits::Unsigned T>
[[nodiscard]] inline constexpr std::vector<T> get_prime_factors(T value) noexcept {
  // TODO:
  return {};
}

template<traits::Unsigned T> [[nodiscard]] inline constexpr T get_next_prime(T value) noexcept {
  // TODO:
  return T{ 0 };
}

}  // namespace hx::integral

#endif
