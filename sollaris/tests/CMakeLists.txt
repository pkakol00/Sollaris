cmake_minimum_required(VERSION 3.0.0)

# cmake_policy(SET CMP0079 NEW)

include(CTest)

set(TEST_NAME my_tests)
set(TEST_SOURCES
  # Sources for tests
  DummyTest.cpp
)

add_subdirectory(googletest)

add_executable(${TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_NAME} PUBLIC GTest::gtest_main)
include(GoogleTest)

gtest_discover_tests(${TEST_NAME})


