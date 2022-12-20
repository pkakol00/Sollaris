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
    Vec3 color = Vec3(12, 12, 3);
    PlanetData obiekt = PlanetData(1000.0, 50.0, color, color, 0);
    std::cout << obiekt.mass << ", " << obiekt.radious << ", (" << obiekt.velocity.x << ", " << obiekt.velocity.y <<
    ", " << obiekt.velocity.z << "), (" << obiekt.colour.x << ", " << obiekt.colour.y << ", " << obiekt.colour.z << "), " << obiekt.planet_id << std::endl;
    std::string a = obiekt.serialize();
    PlanetData newOb = *(obiekt.deserialize(a));
    std::cout << newOb.mass << ", " << newOb.radious << ", (" << newOb.velocity.x << ", " << newOb.velocity.y <<
    ", " << newOb.velocity.z << "), (" << newOb.colour.x << ", " << newOb.colour.y << ", " << newOb.colour.z << "), " << newOb.planet_id << std::endl;

    std::deque<Vec3> test;
    test.push_back(color);
    Vec3 color2 = Vec3(15, 16, 17);
    test.push_back(color2);
    PlanetPosition obiekt2 = PlanetPosition(test, 0);
    std::cout << obiekt2.planet_id << std::endl;
    for(auto i : obiekt2.positions ) {
      std::cout << " (" << i.x << ", " << i.y << ", " << i.z << ", ";
    }
    std::cout << ")" << std::endl;
    std::string b = obiekt2.serialize();
    PlanetPosition newOb2 = *(obiekt2.deserialize(b));
    std::cout << newOb2.planet_id << std::endl;
    for(auto i : newOb2.positions ) {
      std::cout << " (" << i.x << ", " << i.y << ", " << i.z << ", ";
    }
    std::cout << ")" << std::endl;}