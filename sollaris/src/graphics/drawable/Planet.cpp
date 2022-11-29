#include "Planet.h"
#include <GL/glew.h>

#include <vector>
#include <glm/gtc/constants.hpp>


std::vector<glm::vec3> createVerteceis(int n, float radious) {
  std::vector<glm::vec3> v(n + 1);
  v[0] = glm::vec3(0);
  for (int i = 0; i < n; i ++) {
    float angle = glm::two_pi<float>() / (float)n * (float)i;
    v[i + 1] = glm::vec3(glm::sin(angle) * radious, glm::cos(angle) * radious, 0.0);
  }
  return v;
}

std::vector<uint> createIndecies(int n) {
  std::vector<uint> v(3 * n);
  for (uint i = 0; i < n - 1; i ++) {
    v[3 * i] = 0;
    v[3 * i + 1] = i + 1;
    v[3 * i + 2] = i + 2;
  }
    v[3 * (n - 1)] = 0;
    v[3 * (n - 1) + 1] = n;
    v[3 * (n - 1) + 2] = 1;
  return v;
}

Planet::Planet(int granulation, float radious) {
  indecies = createIndecies(granulation);
  vertecies = createVerteceis(granulation, radious);

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecies.size() * sizeof(uint),
               indecies.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, 3 * vertecies.size() * sizeof(float),
               vertecies.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  LOG("Created model: " + std::to_string(VAO));
}

void Planet::draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indecies.size(), GL_UNSIGNED_INT, 0);
}
