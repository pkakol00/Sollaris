cmake_minimum_required(VERSION 3.0.0)

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

add_subdirectory(tests)
