find_package(GTest REQUIRED)

enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

set(INTEGRAL_TESTS
    integral/integral-test.cpp)

add_executable(integralTests ${INTEGRAL_TESTS})
target_link_libraries(integralTests GTest::gtest GTest::gtest_main HOMOMORPHIX_LIB)

add_test(IntegralTests integralTests)
