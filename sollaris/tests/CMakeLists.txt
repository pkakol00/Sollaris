cmake_minimum_required(VERSION 3.0.0)

# cmake_policy(SET CMP0079 NEW)

include(CTest)

set(TEST_NAME my_tests)
set(TEST_SOURCES
  # Sources for tests
  DummyTest.cpp
  Vec3Test.cpp
  PhysicsTest.cpp
  IOTest.cpp
  ../src/util/serializable.cpp
  ../src/util/common.cpp
  ../src/util/common.h
  ../src/physics/PhysicsEngine.cpp
  ../src/physics/PhysicsEngine.h
  ../src/util/serializable.cpp
  ../src/util/serializable.capnp
  IOTest.cpp
  ../src/io/IO.cpp
  ../src/io/IO.h
)

find_package(
    CapnProto REQUIRED HINTS
    "${CMAKE_CURRENT_SOURCE_DIR}/../lib_gcc/cmake/capnp"
)

add_subdirectory(googletest)

add_executable(${TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_NAME} PUBLIC GTest::gtest_main)
target_link_libraries(
    ${TEST_NAME} PUBLIC CURL::libcurl
    ${CAPNP_LIBRARIES}
)

target_include_directories(
    ${TEST_NAME} PUBLIC CURL::libcurl
    ${CAPNP_LIBRARIES_DIRS}
)

include(GoogleTest)

gtest_discover_tests(${TEST_NAME})
