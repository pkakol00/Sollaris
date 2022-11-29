#include "GraphicsEngine.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <SFML/OpenGL.hpp>
#include <string>
#include "../util/Log.h"

#include <graphics/drawable/Triangle.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GraphicsEngine::GraphicsEngine()
    : window_ptr(std::make_shared<sf::Window>(sf::VideoMode(800, 600),
                                              "OpenGL",
                                              sf::Style::Default,
                                              sf::ContextSettings(32))) {
  window_ptr->setVerticalSyncEnabled(true);
  window_ptr->setActive(true);

  init();

  glClearColor(.66, .66, .55, 1);

  shader = ge::Shader("resources/shaders/basic");
}

bool GraphicsEngine::pollEvents() {
  sf::Event event;
  bool res = true;
  while (window_ptr->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      // end the program
      res = false;
    } else if (event.type == sf::Event::Resized) {
      // adjust the viewport when the window is resized
      glViewport(0, 0, event.size.width, event.size.height);
    }
  }
  return res;
}

bool GraphicsEngine::display() {
  static Triangle t;

  t.position = glm::vec3(0);
  t.rotation = glm::vec3(0);
  t.scale    = glm::vec3(1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  auto res = pollEvents();
  shader.bind();

  shader.setUniformVec4("my_color", glm::vec4(1.0));
  shader.setUniformMat4("model", t.getModelMatrix());
  t.draw();

  window_ptr->display();
  return res;
}

void GraphicsEngine::init() {
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    LOG("ERROR: " +
        std::string(reinterpret_cast<const char*>(glewGetErrorString(err))));
  }
  LOG(std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
}