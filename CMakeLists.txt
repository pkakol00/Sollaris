cmake_minimum_required(VERSION 3.0.0)
project(Foo VERSION 0.1.0)

include(CTest)
enable_testing()

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

add_executable(Foo ${SOURCES})
set_property(TARGET Foo PROPERTY CXX_STANDARD 20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
