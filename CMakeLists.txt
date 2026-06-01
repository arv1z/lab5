cmake_minimum_required(VERSION 3.10)
project(lab05)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(banking)

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)

    add_executable(check tests/test.cpp)

    target_link_libraries(check
        banking
        GTest::GTest
        GTest::Main
	gmock
	gmock_main
        pthread
    )

    add_test(NAME check COMMAND check)
endif()
