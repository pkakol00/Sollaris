#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(std::shared_ptr<std::vector<PlanetPosition>> position, std::shared_ptr<std::vector<PlanetData>> data, double interval)
  : position(position), data(data), interval(interval), G(6.6743015e-10) {}
