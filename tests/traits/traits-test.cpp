#include <gtest/gtest.h>

#include <integral/integral.hpp>
#include <traits/traits.hpp>

namespace hx::test::traits {

template<typename T> inline constexpr void check_narrow_same() {
  static_assert(!hx::traits::is_narrowing_v<T, T>);
}

TEST(narrowing, same_type) {
  check_narrow_same<int8_t>();
  check_narrow_same<int16_t>();
  check_narrow_same<int32_t>();
  check_narrow_same<int64_t>();
  check_narrow_same<uint8_t>();
  check_narrow_same<uint16_t>();
  check_narrow_same<uint32_t>();
  check_narrow_same<uint64_t>();

  check_narrow_same<signed char>();
  check_narrow_same<unsigned char>();
  check_narrow_same<short int>();
  check_narrow_same<unsigned short int>();
  check_narrow_same<unsigned int>();
  check_narrow_same<int>();
  check_narrow_same<long int>();
  check_narrow_same<unsigned long int>();
  check_narrow_same<long long int>();
  check_narrow_same<unsigned long long int>();

  check_narrow_same<std::size_t>();
  check_narrow_same<bool>();

  check_narrow_same<float>();
  check_narrow_same<double>();
  check_narrow_same<long double>();
}

TEST(narrowing, integral_smaller_to_bigger_same_sign) {
  static_assert(!hx::traits::is_narrowing_v<int8_t, int16_t>);
  static_assert(!hx::traits::is_narrowing_v<signed char, int16_t>);
  static_assert(!hx::traits::is_narrowing_v<short, int64_t>);
  static_assert(!hx::traits::is_narrowing_v<int, int64_t>);
  static_assert(!hx::traits::is_narrowing_v<long int, int64_t>);
  static_assert(!hx::traits::is_narrowing_v<long long int, int64_t>);

  static_assert(!hx::traits::is_narrowing_v<uint8_t, uint16_t>);
  static_assert(!hx::traits::is_narrowing_v<unsigned char, uint16_t>);
  static_assert(!hx::traits::is_narrowing_v<unsigned short, uint64_t>);
  static_assert(!hx::traits::is_narrowing_v<unsigned int, uint64_t>);
  static_assert(!hx::traits::is_narrowing_v<unsigned long int, uint64_t>);
  static_assert(!hx::traits::is_narrowing_v<unsigned long long int, uint64_t>);
  static_assert(!hx::traits::is_narrowing_v<std::size_t, uint64_t>);
}

TEST(narrowing, float_smaller_to_bigger) {
  static_assert(!hx::traits::is_narrowing_v<float, long double>);
  static_assert(!hx::traits::is_narrowing_v<double, long double>);
  static_assert(!hx::traits::is_narrowing_v<float, double>);
}

TEST(narrowing, float_bigger_to_smaller) {
  static_assert(hx::traits::is_narrowing_v<long double, float>);
  static_assert(hx::traits::is_narrowing_v<long double, double>);
  static_assert(hx::traits::is_narrowing_v<double, float>);
}

TEST(narrowing, integral_bigger_to_smaller_same_sign) {
  static_assert(hx::traits::is_narrowing_v<int64_t, int8_t>);
  static_assert(hx::traits::is_narrowing_v<uint64_t, unsigned int>);
}

TEST(narrowing, integral_different_sign) {
  static_assert(hx::traits::is_narrowing_v<int32_t, uint32_t>);
  static_assert(hx::traits::is_narrowing_v<uint32_t, int32_t>);
}

TEST(narrowing, float_to_integral) {
  static_assert(hx::traits::is_narrowing_v<float, int64_t>);
  static_assert(hx::traits::is_narrowing_v<float, uint64_t>);
}

TEST(narrowing, integral_to_float) {
  static_assert(hx::traits::is_narrowing_v<int8_t, float>);
  static_assert(hx::traits::is_narrowing_v<uint8_t, double>);
}
}  // namespace hx::test::traits
