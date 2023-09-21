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
[[nodiscard]] inline constexpr bool is_value_fittable(
    [[maybe_unused]] From from) noexcept {
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
[[nodiscard]] inline constexpr std::optional<To> secure_cast(
    From from) noexcept {
  if (is_value_fittable<From, To>(from)) return static_cast<To>(from);
  return std::nullopt;
}

}  // namespace hx::integral

#endif
