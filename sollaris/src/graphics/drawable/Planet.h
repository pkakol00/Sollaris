#ifndef __PLANET_H__
#define __PLANET_H__

#include "Triangle.h"
#include "glm/glm.hpp"
#include <vector>

class Planet: public Drawable {
  private:
    uint VAO, VBO, EBO;

    std::vector<uint> indecies;
    std::vector<glm::vec3> vertecies;

   public:
    void draw() override;
    Planet() = default;
    Planet(int granulation, float radious);
};

#endif // __PLANET_H__