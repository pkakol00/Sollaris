#ifndef __ORBIT_H__
#define __ORBIT_H__

#include "Drawable.h"

#include <util/common.h>
#include <deque>

class Orbit : public Drawable {
  private:
    uint VAO, VBO, EBO;

    std::vector<uint> indecies;
    // std::vector<glm::vec3> vertecies;

    std::deque<Vec3>* orbit_points;

   public:
    void draw() override;
    Orbit() = default;
    Orbit(std::deque<Vec3>* orbit_points);
};
#endif // __ORBIT_H__