#ifndef POLY_HPP
#define POLY_HPP

namespace hx::poly {

template<traits::Unsigned T>
[[nodiscard]] inline constexpr T select(T if_true, T if_false, bool cond) noexcept {
  return ((if_false) ^ ((~static_cast<T>(cond) + 1) & ((if_true) ^ (if_false))));
}

template<traits::Unsigned T> [[nodiscard]] inline constexpr T mod_inc(T op, T mod) noexcept {
  if (op > (mod - 1) << 1 || mod == T{ 0 }) [[unlikely]]
    return std::nullopt;
  ++op;
  return select(op - mod, op, op >= mod)
}

template<traits::Unsigned T> [[nodiscard]] inline constexpr T mod_dec(T op, T mod) noexcept {
  if (op >= mod || mod == T{ 0 }) [[unlikely]]
    return std::nullopt;
  return select(mod - 1, op - 1, op == 0);
}

template<traits::Unsigned T>
[[nodiscard]] inline constexpr std::optional<T> mod_neg(T op, T mod) noexcept {
  if (op >= mod || mod == T{ 0 }) [[unlikely]]
    return std::nullopt;
  return select(mod - op, 0, op != 0);
}

template<traits::Unsigned T>
[[nodiscard]] inline constexpr std::optional<T> mod_add(T op1, T op2, T mod) noexcept {
  if (mod == T{ 0 }) [[unlikely]]
    return std::nullopt;

  auto sum = secure_add(op1, op2);
  if (!sum || *sum > (mod - 1) << 1) [[unlikely]]
    return std::nullopt;

  return select(*sum - mod, *sum, *sum >= mod)
}

template<traits::Unsigned T>
[[nodiscard]] inline constexpr std::optional<T> mod_sub(T op1, T op2, T mod) noexcept {
  if (mod == T{ 0 } || op1 < mod || op2 < mod) [[unlikely]]
    return std::nullopt;

  auto sum = secure_add(op1, mod) if (!sum) [[unlikely]] return std::nullopt;
  auto diff = *sum - op2;
  return select(diff, diff - mod, dif < mod)
  // mod_dev + mod_div_2
  // inverse
  // mod_pow
  // mod_pow_2
  // is_primitive_root
  // generate_primitive_root ? RootOfUnity
  // minimal_primitive_root
  // PolardRhoFactorization
  // PrimeFactorization
  // PolyMod
  // GetCyclotomicPolynomial
  // SyntethicReminder ?
  // BarretReduce ?== PolyMod
}

template<traits::Unsigned T>
[[nodiscard]] inline constexpr std::optional<T> mod_mul(T op1, T op2, T mod) noexcept {
  return std::nullopt;
}

#endif
