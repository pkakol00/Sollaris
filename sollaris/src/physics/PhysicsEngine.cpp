#ifndef __PHYSICSENINE_H__
#define __PHYSICSENINE_H__

#include "../util/events.h"
#include <vector>

class PhysicsEngine{
public:
  void update();
  CREATE_EVENT(planet_merge, void, std::vector<int>, int);
  CREATE_EVENT(planet_division, int, std::vector<int>);

};

#endif // __PHYSICSENINE_H__