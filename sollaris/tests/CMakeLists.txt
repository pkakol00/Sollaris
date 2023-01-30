cmake_minimum_required(VERSION 3.0.0)

# cmake_policy(SET CMP0079 NEW)

include(CTest)

set(TEST_NAME my_tests)
set(TEST_SOURCES
  # Sources for tests
  DummyTest.cpp
  Vec3Test.cpp
  PhysicsTest.cpp
  ../src/util/common.cpp
  ../src/util/common.h
  ../src/physics/PhysicsEngine.cpp
  ../src/physics/PhysicsEngine.h
  IOTest.cpp
  ../src/io/IO.cpp
  ../src/io/IO.h
)

add_subdirectory(googletest)

add_executable(${TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_NAME} PUBLIC GTest::gtest_main)
target_link_libraries(${TEST_NAME} PUBLIC CURL::libcurl)
include(GoogleTest)

gtest_discover_tests(${TEST_NAME})


