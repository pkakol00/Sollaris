#include "PhysicsEngine.h"
#include <cmath>

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
    position->at(i).positions.push_back(newPosition);
  }
}

void join_sets(int index, std::vector<std::set<int>> &sets) {
    for(const auto &i: sets.at(index)) {
        sets.at(i).erase(index);
    }

    for(const auto &i: sets.at(index)) {
        join_sets(i, sets);
    }

    for(const auto &i: sets.at(index)) {
        sets.at(index).merge(sets.at(i));
        sets.at(i).clear();
    }
}

std::vector<std::set<int>> PhysicsEngine::findCollisions() {
  std::vector<std::set<int>> collisions(this->data->size(), std::set<int>());

  for(int i = 0; i < this->data->size(); ++i) {
    auto Ad = this->data->at(i);
    auto Ap = this->position->at(i).positions.back();

    for(int j = i + 1; j < this->data->size(); ++j) {
      auto Bd = this->data->at(j);
      auto Bp = this->position->at(j).positions.back();
      LOG("Checking collision of ", Ad.planet_id, " with ", Bd.planet_id);

      auto squared_distance = (Ap - Bp).squaredLength();
      auto radious_sum = std::pow(Ad.radious + Bd.radious, 2.0);

      if(squared_distance <= radious_sum) {
        LOG("Detected collision of ", Ad.planet_id, " with ", Bd.planet_id);
        collisions.at(i).insert(j);
      }
    }
  }

  for(int i = 0; i < collisions.size(); ++i) {
    LOG("Joining collissions with: ", this->data->at(i).planet_id);
    join_sets(i, collisions);
  }

  return collisions;
}

void PhysicsEngine::resolveCollisions(const std::vector<std::set<int>> &collisions) {
  std::set<int> id_to_remove;
  for(int i = 0; i < collisions.size(); ++i) {
    auto collision = collisions.at(i);

    if(collision.empty()) {
      continue;
    }

    collision.insert(this->data->at(i).planet_id);
    id_to_remove.merge(mergePlanets(collision));

    std::vector<int> ids;
    for(const auto j : collision) {
        ids.push_back(this->data->at(j).planet_id);
    }
    planet_merge_event_function(ids, this->data->back().planet_id);
  }

  if(!id_to_remove.empty()) {
    removePlanets(id_to_remove);
  }
}

std::set<int> PhysicsEngine::mergePlanets(const std::set<int>& planets) {
  LOG("Merging collided objects");

  std::set<int> id_to_remove;
  auto tmp = this->data->at(*planets.begin());

  PlanetPosition new_object_pos;
  new_object_pos.planet_id = this->data->back().planet_id + 1;

  PlanetData new_object_data {0.0, 0.0, {0.0, 0.0, 0.0}, tmp.colour, new_object_pos.planet_id};

  double mass_sum = 0.0;
  Vec3 pos {0.0, 0.0, 0.0};

  for(const auto &j : planets) {
      tmp = this->data->at(j);
      LOG("Adding object: ", tmp.planet_id, " to new object");
      id_to_remove.insert(tmp.planet_id);

      new_object_data.mass += tmp.mass;
      new_object_data.radious += tmp.radious * tmp.radious * tmp.radious;
      new_object_data.velocity += tmp.velocity * tmp.mass;

      pos += this->position->at(j).positions.back() * tmp.mass;

      mass_sum += tmp.mass;
  }

  new_object_data.radious = std::cbrt(new_object_data.radious);
  new_object_data.velocity = new_object_data.velocity / mass_sum;

  new_object_pos.positions.push(pos / mass_sum);

  LOG("Merged object: id       - ", new_object_data.planet_id);
  LOG("Merged object: mass     - ", new_object_data.mass);
  LOG("Merged object: radious  - ", new_object_data.radious);
  LOG("Merged object: colour   - ", new_object_data.colour);
  LOG("Merged object: velocity - ", new_object_data.velocity);
  LOG("Merged object: position - ", new_object_pos.positions.back());

  this->data->push_back(new_object_data);
  this->position->push_back(new_object_pos);

  return id_to_remove;
}

void PhysicsEngine::removePlanets(const std::set<int>& ids) {
  for(int i = 0; i < this->data->size();) {
    auto id = this->data->at(i).planet_id;
    if(ids.find(id) == ids.end()) {
      ++i;
      continue;
    }

    LOG("Removal of collided object: ", id);
    this->data->erase(this->data->begin() + i);
    this->position->erase(this->position->begin() + i);
  }
}

PhysicsEngine::PhysicsEngine(std::shared_ptr<std::vector<PlanetPosition>> position, std::shared_ptr<std::vector<PlanetData>> data, double interval)
  : position(position), data(data), interval(interval), G(6.6743015e-11) {
    planet_merge_event_function = [](std::vector<int> _, int __) { LOG("Missing callback for planet merge event"); };
    planet_division_event_function = [](int _, std::vector<int> __) { LOG("Missing callback for planet division event"); };
}

void PhysicsEngine::update() {
  updateVelocities();
  updatePositions();
  auto collisions = findCollisions();
  resolveCollisions(collisions);
}
