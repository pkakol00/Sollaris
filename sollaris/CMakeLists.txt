cmake_minimum_required(VERSION 3.12.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

set(GRAPHIC_SOURCES
  src/graphics/GraphicsEngine.cpp
  src/graphics/GraphicsEngine.h
  src/graphics/Camera.cpp
  src/graphics/Camera.h
  src/graphics/Shader.cpp
  src/graphics/Shader.h
  src/graphics/drawable/Drawable.h
  src/graphics/drawable/Drawable.cpp
  src/graphics/drawable/Triangle.h
  src/graphics/drawable/Triangle.cpp
  src/graphics/drawable/Planet.cpp
  src/graphics/drawable/Planet.h
  src/graphics/drawable/Orbit.cpp
  src/graphics/drawable/Orbit.h
)

set(IO_SOURCES
  src/io/IO.h
  src/io/IO.cpp
)

set(PHYSICS_SOURCES
  src/physics/PhysicsEngine.cpp
  src/physics/PhysicsEngine.h
)

set(UTILS_SOURCES
  src/util/common.cpp
  src/util/common.h
)

set(SOURCES
  src/main.cpp
  ${GRAPHIC_SOURCES}
  ${IO_SOURCES}
  ${PHYSICS_SOURCES}
  ${UTILS_SOURCES}
)

find_package(SFML 2 COMPONENTS graphics window audio 
  REQUIRED HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../lib_gcc/cmake/SFML")

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} 
  ${GTKMM_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  -lGLEW
  sfml-graphics sfml-window sfml-audio)

target_include_directories(${PROJECT_NAME} PUBLIC 
  ${GTKMM_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
  "${CMAKE_CURRENT_SOURCE_DIR}/../include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)
target_compile_options(${PROJECT_NAME} PUBLIC ${GTKMM_CFLAGS_OTHER})

add_custom_target(COPY_RESOURCES ALL
  COMMAND cp -r
  "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_CURRENT_BINARY_DIR}"
)

add_subdirectory(tests)
