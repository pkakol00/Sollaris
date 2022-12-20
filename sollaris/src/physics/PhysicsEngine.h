#ifndef __PHYSICSENINE_H__
#define __PHYSICSENINE_H__

#include "../util/events.h"
#include "../util/common.h"
#include <vector>
#include <memory>
#include <cmath>

class PhysicsEngine {
  std::shared_ptr<std::vector<PlanetPosition>> position;
  std::shared_ptr<std::vector<PlanetData>> data;
  double interval;
  const double G;

  void updateVelocities();
  void updatePositions();
public:
  PhysicsEngine(std::shared_ptr<std::vector<PlanetPosition>>, std::shared_ptr<std::vector<PlanetData>>, double);
  void update();
  CREATE_EVENT(planet_merge, void, std::vector<int>, int);
  CREATE_EVENT(planet_division, void, int, std::vector<int>);

};

#endif // __PHYSICSENINE_H__
