find_package(GTest REQUIRED)

enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

#----------
set(INTEGRAL_TESTS
    integral/integral-test.cpp)

add_executable(RunIntegralTests ${INTEGRAL_TESTS})
target_link_libraries(RunIntegralTests GTest::gtest GTest::gtest_main HOMOMORPHIX_LIB)

add_test(IntegralTests RunIntegralTests)

#----------
set(TRAITS_TESTS
    integral/traits-test.cpp)

add_executable(RunTraitsTests ${INTEGRAL_TESTS})
target_link_libraries(RunTraitsTests GTest::gtest GTest::gtest_main HOMOMORPHIX_LIB)

add_test(TraitsTests RunTraitsTests)
