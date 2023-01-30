cmake_minimum_required(VERSION 3.0.0)

find_package(PkgConfig REQUIRED)
find_package(CURL REQUIRED) 
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules(CURL REQUIRED libcurl )

set(GRAPHIC_SOURCES
  src/graphics/GraphicsEngine.cpp
  src/graphics/GraphicsEngine.h
)

set(IO_SOURCES
  src/io/IO.h
  src/io/IO.cpp
  src/io/json.hpp
)

set(PHYSICS_SOURCES
  src/physics/PhysicsEngine.cpp
  src/physics/PhysicsEngine.h

)

set(UTILS_SOURCES
  src/util/common.cpp
  src/util/common.h
  src/util/serializable.cpp
  src/util/serializable.capnp
  )

set(SOURCES
  src/main.cpp
  ${GRAPHIC_SOURCES}
  ${IO_SOURCES}
  ${PHYSICS_SOURCES}
  ${UTILS_SOURCES}
)

find_package(CapnProto REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../lib_gcc/cmake/capnp")

add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} 
  ${GTKMM_LIBRARIES}
  ${CAPNP_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PUBLIC 
  ${GTKMM_INCLUDE_DIRS}
  ${CAPNP_INCLUDE_DIRS}
)

target_compile_options(${PROJECT_NAME} PUBLIC ${GTKMM_CFLAGS_OTHER})

target_link_libraries(${PROJECT_NAME}  ${CURL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CURL_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${CURL_CFLAGS_OTHER})


add_subdirectory(tests)
