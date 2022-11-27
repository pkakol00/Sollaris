#include "PhysicsEngine.h"

void PhysicsEngine::updatePositions() {
  LOG("Updating positions of all objects");
  for(int i = 0; i < this->data->size(); i++) {
    LOG("New position for object with id: " + std::to_string(data->at(i).planet_id));
    Vec3 newPosition = position->at(i).positions.back() + data->at(i).velocity * this->interval;
    position->at(i).positions.push(newPosition);
  }
}

PhysicsEngine::PhysicsEngine(std::shared_ptr<std::vector<PlanetPosition>> position, std::shared_ptr<std::vector<PlanetData>> data, double interval)
  : position(position), data(data), interval(interval), G(6.6743015e-10) {}

void PhysicsEngine::update() {
  updatePositions();
}
