cmake_minimum_required(VERSION 3.0.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

set(GRAPHIC_SOURCES
  src/graphics/GraphicsEngine.cpp
  src/graphics/GraphicsEngine.h
)

set(IO_SOURCES
  src/io/IO.h
  src/io/IO.cpp
)

set(PHYSICS_SOURCES
  src/physics/PhysicsEngine.cpp
  src/physics/PhysicsEngine.h
)

set(SOURCES
  src/main.cpp
  ${GRAPHIC_SOURCES}
  ${IO_SOURCES}
  ${PHYSICS_SOURCES}
)

add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${GTKMM_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${GTKMM_CFLAGS_OTHER})

add_subdirectory(tests)
