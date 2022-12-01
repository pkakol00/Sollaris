#include "graphics/GraphicsEngine.h"
#include "physics/PhysicsEngine.h"
#include "io/IO.h"
#include <util/common.h>

#include <chrono>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 get_position(float offset, float speed, float radious = 1.0) {
  int p = std::chrono::steady_clock::now().time_since_epoch().count();
  float t = offset + (float)p / 1000000.0 * speed;
  return glm::vec3(glm::sin(glm::radians(t)) * radious,
                   glm::cos(glm::radians(t)) * radious, 0.0);
} 

Vec3 cast(glm::vec3 v) {
  return {v.x, v.y, v.z};
} 

int main() {
  GraphicsEngine graphics;
  
  PlanetData A = {100.0, 1.0, 1.0, {1.0, 1.0, 0.0}, 0};
  PlanetData B = {100.0, 1.0, 1.0, {-1.0, -1.0, 0.0}, 1};
  
  std::vector<PlanetData> planet_data = {A, B};
  auto planet_data_ptr = std::make_shared<std::vector<PlanetData>>(planet_data);

  PlanetPosition A_pos = {std::deque<Vec3>({{1.0, 0.0, 0.0}}), 0};
  PlanetPosition B_pos = {std::deque<Vec3>({{-1.0, 0.0, 0.0}}), 1};
  PlanetPosition C_pos = {std::deque<Vec3>({{-2.0, 0.0, 0.0}}), 1};


  std::vector<PlanetPosition> planet_pos = {A_pos, B_pos, C_pos};
  auto planet_pos_ptr = std::make_shared<std::vector<PlanetPosition>>(planet_pos);

  for (int i = 0; i < 100; i ++) {
    planet_pos_ptr->at(0).positions.push_front(cast(get_position(0.0, 0.1)));
    planet_pos_ptr->at(1).positions.push_front(cast(get_position(180.0, 0.1)));
    planet_pos_ptr->at(2).positions.push_front(cast(get_position(90.0, 0.2, 2.0)));
  }

  graphics.setPlanetPositions(planet_pos_ptr);
  
  while (true) {

    // mock-up of physics
    planet_pos_ptr->at(0).positions.push_front(cast(get_position(0.0, 0.1)));
    planet_pos_ptr->at(1).positions.push_front(cast(get_position(180.0, 0.1)));
    planet_pos_ptr->at(2).positions.push_front(cast(get_position(90.0, 0.2, 2.0)));
    planet_pos_ptr->at(0).positions.pop_back();
    planet_pos_ptr->at(1).positions.pop_back();
    planet_pos_ptr->at(2).positions.pop_back();

    if (!graphics.display()) break;
  }
}