#ifndef INTEGRAL_HPP
#define INTEGRAL_HPP

#include <optional>
#include "xsimd/xsimd.hpp"

namespace hx::integral {

template <typename D>
[[nodiscard]] inline std::optional<D> cast(auto value) noexcept {
    using B_in = xsimd::batch<decltype(value)>;
    using B_out = xsimd::batch<D>;
    using T_in = typename B_in::value_type;
    using T_out = typename B_out::value_type;
    using B_common_in = xsimd::batch<T_in>;
    using B_common_out = xsimd::batch<T_out>;
    
    T_in in_test_value = static_cast<T_in>(value);
    B_common_out res = xsimd::batch_cast<T_out>(B_common_in(in_test_value));

    return res.get(0);
}

}

#endif
