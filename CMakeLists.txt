cmake_minimum_required(VERSION 3.19)

project (HomomorphiX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Werror)

add_subdirectory(dependencies)

add_library(HOMOMORPHIX_LIB INTERFACE)
target_link_libraries(HOMOMORPHIX_LIB INTERFACE
    $<BUILD_INTERFACE:xsimd>)
target_include_directories(HOMOMORPHIX_LIB SYSTEM INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

option(HX_BENCHMARK "Enable benchmarking" OFF)
option(HX_TEST "Enable tests" ON)
option(HX_EXAMPLES "Enable examples" OFF)

if (HX_BENCHMARK)
    add_subdirectory(benchmarks)
endif()

if (HX_TEST)
    add_subdirectory(tests)
endif()

if (HX_EXAMPLES)
    add_subdirectory(examples)
endif()
