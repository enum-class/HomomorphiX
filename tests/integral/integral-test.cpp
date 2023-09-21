#include <gtest/gtest.h>

#include <integral/integral.hpp>

namespace hx::test::integral {

template<typename From, typename To = From>
inline constexpr bool check(std::optional<From> from = std::nullopt) {
  From value = std::numeric_limits<From>::max();
  if (from) value = *from;
  return hx::integral::is_value_fittable<From, To>(value);
}

TEST(is_value_fittable, same_type) {
  constexpr int8_t val = 100;
  static_assert(hx::integral::is_value_fittable<int8_t, int8_t>(val));

  EXPECT_TRUE(check<uint64_t>());
  EXPECT_TRUE(check<size_t>());
  EXPECT_TRUE(check<double>());
  EXPECT_TRUE(check<bool>());
}

TEST(is_value_fittable, integral_smaller_to_bigger_same_sign) {
  {
    auto val = check<uint16_t, uint64_t>();
    EXPECT_TRUE(val);
  }
  {
    auto val = check<int16_t, int64_t>();
    EXPECT_TRUE(val);
  }
  {
    auto val = check<size_t, uint64_t>();
    EXPECT_TRUE(val);
  }
}

TEST(is_value_fittable, float_smaller_to_bigger) {
  auto val = check<float, double>();
  EXPECT_TRUE(val);
}

TEST(is_value_fittable, float_bigger_to_smaller) {
  {
    auto val = check<double, float>();
    EXPECT_FALSE(val);
  }
  {
    auto val = check<double, float>(2.4);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<double, float>(-6.4);
    EXPECT_TRUE(val);
  }
}

TEST(is_value_fittable, integral_bigger_to_smaller_same_sign) {
  {
    auto val = check<uint64_t, uint8_t>(300);
    EXPECT_FALSE(val);
  }
  {
    auto val = check<uint64_t, uint8_t>(1);
    EXPECT_TRUE(val);
  }
}

TEST(is_value_fittable, integral_different_sign) {
  {
    auto val = check<uint8_t, int8_t>(0);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<uint8_t, int8_t>(200);
    EXPECT_FALSE(val);
  }
  {
    auto val = check<int8_t, uint8_t>(0);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<int8_t, uint8_t>();
    EXPECT_TRUE(val);
  }
  {
    auto val = check<int8_t, uint8_t>(-27);
    EXPECT_FALSE(val);
  }
}

TEST(is_value_fittable, float_to_integral) {
  {
    auto val = check<float, uint8_t>(0.0);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<float, int8_t>(-13.0);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<float, uint64_t>(-23.0);
    EXPECT_FALSE(val);
  }
  {
    auto val = check<float, uint64_t>();  // ?
    EXPECT_FALSE(val);
  }
  {
    auto val = check<float, int8_t>(0.0);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<float, int64_t>(-23.0);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<float, int64_t>();  // ?
    EXPECT_FALSE(val);
  }
  {
    auto val = check<double, uint64_t>(0.0);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<double, uint64_t>(-23.0);
    EXPECT_FALSE(val);
  }
  {
    auto val = check<float, uint64_t>();  // ?
    EXPECT_FALSE(val);
  }
  {
    auto val = check<float, int64_t>(0.0);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<float, int8_t>(-23.0);
    EXPECT_TRUE(val);
  }
}

TEST(is_value_fittable, integral_to_float) {
  {
    auto val = check<uint16_t, double>();
    EXPECT_TRUE(val);
  }
  {
    auto val = check<uint16_t, double>(100);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<int16_t, double>(-100);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<uint64_t, double>();
    EXPECT_TRUE(val);
  }
  {
    auto val = check<uint16_t, float>();
    EXPECT_TRUE(val);
  }
  {
    auto val = check<uint16_t, float>(100);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<int16_t, float>(-100);
    EXPECT_TRUE(val);
  }
  {
    auto val = check<uint64_t, float>();
    EXPECT_TRUE(val);
  }
}

}  // namespace hx::test::integral
