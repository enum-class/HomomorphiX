#include <gtest/gtest.h>
#include <integral/integral.hpp>

TEST(cast, sama_type) {
    uint32_t s = 23;
    int expected = 23;
    
    auto d = hx::integral::cast<int>(s);
    EXPECT_EQ(d, expected);
}
