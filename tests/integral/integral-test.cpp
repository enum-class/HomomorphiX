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

TEST(secure_cast, same_type) {
  constexpr double val = 100.0;
  constexpr int8_t exp_val = 100;
  static_assert(*hx::integral::secure_cast<int8_t>(val) == exp_val);

  {
    int8_t val = 23;
    int8_t exp_val = 23;
    int8_t cast_val = *hx::integral::secure_cast<int8_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
  {
    int8_t val = -23;
    int8_t exp_val = -23;
    int8_t cast_val = *hx::integral::secure_cast<int8_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
  {
    uint8_t val = 23;
    uint8_t exp_val = 23;
    uint8_t cast_val = *hx::integral::secure_cast<uint8_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
  {
    float val = 23.2;
    float exp_val = 23.2;
    float cast_val = *hx::integral::secure_cast<float>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
  {
    double val = -23.5;
    double exp_val = -23.5;
    double cast_val = *hx::integral::secure_cast<double>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
}

TEST(secure_cast, integral_smaller_to_bigger_same_sign) {
  {
    int8_t val = 0;
    int32_t exp_val = 0;
    int32_t cast_val = *hx::integral::secure_cast<int32_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
  {
    int8_t val = -23;
    int64_t exp_val = -23;
    int64_t cast_val = *hx::integral::secure_cast<int64_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
  {
    uint8_t val = 255;
    uint16_t exp_val = 255;
    uint16_t cast_val = *hx::integral::secure_cast<uint16_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
}

TEST(secure_cast, float_smaller_to_bigger_same_sign) {
  {
    float val = 23.2;
    double exp_val = 23.2;
    double cast_val = *hx::integral::secure_cast<double>(val);
    EXPECT_NEAR(cast_val, exp_val, 1e-2);
  }
  {
    float val = -23.5;
    long double exp_val = -23.5;
    long double cast_val = *hx::integral::secure_cast<long double>(val);
    EXPECT_DOUBLE_EQ(cast_val, exp_val);
  }
}

TEST(secure_cast, integral_bigger_to_samller_same_sign) {
  {
    int64_t val = 46;
    int32_t exp_val = 46;
    int32_t cast_val = *hx::integral::secure_cast<int32_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
  {
    int32_t val = -23;
    int16_t exp_val = -23;
    int16_t cast_val = *hx::integral::secure_cast<int64_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
  {
    uint64_t val = 2550;
    uint16_t exp_val = 2550;
    uint16_t cast_val = *hx::integral::secure_cast<uint16_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
}

TEST(secure_cast, float_bigger_to_samller) {
  {
    long double val = 23.2;
    double exp_val = 23.2;
    double cast_val = *hx::integral::secure_cast<double>(val);
    EXPECT_DOUBLE_EQ(cast_val, exp_val);
  }
  {
    double val = -23.51;
    float exp_val = -23.51;
    float cast_val = *hx::integral::secure_cast<float>(val);
    EXPECT_DOUBLE_EQ(cast_val, exp_val);
  }
}

TEST(secure_cast, integral_different_sign) {
  {
    int64_t val = 46;
    uint32_t exp_val = 46;
    uint32_t cast_val = *hx::integral::secure_cast<uint32_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
  {
    int32_t val = -23;
    EXPECT_EQ(hx::integral::secure_cast<uint64_t>(val), std::nullopt);
  }
}

TEST(secure_cast, float_to_integral) {
  {
    float val = 46.23;
    uint32_t exp_val = 46;
    uint32_t cast_val = *hx::integral::secure_cast<uint32_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
  {
    double val = -46.23;
    int16_t exp_val = -46;
    int16_t cast_val = *hx::integral::secure_cast<int16_t>(val);
    EXPECT_EQ(cast_val, exp_val);
  }
}

TEST(secure_cast, integral_to_float) {
  {
    int64_t val = 46;
    float exp_val = 46.0;
    float cast_val = *hx::integral::secure_cast<float>(val);
    EXPECT_DOUBLE_EQ(cast_val, exp_val);
  }
  {
    int16_t val = -46;
    double exp_val = -46.0;
    double cast_val = *hx::integral::secure_cast<double>(val);
    EXPECT_DOUBLE_EQ(cast_val, exp_val);
  }
}

}  // namespace hx::test::integral
