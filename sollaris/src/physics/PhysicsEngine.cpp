#include "PhysicsEngine.h"

void PhysicsEngine::updateVelocities() {
  LOG("Updating velocity of all objects");
  std::vector<Vec3> newVelocites(data->size());
  for(int i = 0; i < data->size(); i++) {
    LOG("Updating velocity for object with id: ", data->at(i).planet_id);
    const Vec3 aPos = position->at(i).positions.back();
    const PlanetData aData = data->at(i);

    newVelocites.at(i) = data->at(i).velocity;
    for(int j = 0; j < data->size(); j++) {
      const Vec3 bPos = position->at(j).positions.back();
      const PlanetData bData = data->at(j);

      if(aData.planet_id == bData.planet_id) {
          LOG("Skip updating velocity with self");
          continue;
      }
      LOG("Updating velocity with object with id: ", data->at(j).planet_id);

      double sqrDist = (aPos - bPos).squaredLength();
      Vec3 forceDir = (bPos - aPos).normalized();
      Vec3 force = forceDir * G * aData.mass * bData.mass / sqrDist;
      Vec3 acc = force / aData.mass;

      newVelocites.at(i) += acc * interval;
    }
  }

  for(int i = 0; i < data->size(); i++) {
    data->at(i).velocity = newVelocites.at(i);
    LOG("New velocity of object with id: ", data->at(i).planet_id, " is ", data->at(i).velocity);
  }
}

void PhysicsEngine::updatePositions() {
  LOG("Updating positions of all objects");
  for(int i = 0; i < this->data->size(); i++) {
    LOG("New position for object with id: ", data->at(i).planet_id);
    Vec3 newPosition = position->at(i).positions.back() + data->at(i).velocity * this->interval;
    position->at(i).positions.push(newPosition);
  }
}

PhysicsEngine::PhysicsEngine(std::shared_ptr<std::vector<PlanetPosition>> position, std::shared_ptr<std::vector<PlanetData>> data, double interval)
  : position(position), data(data), interval(interval), G(6.6743015e-11) {}

void PhysicsEngine::update() {
  updateVelocities();
  updatePositions();
}
