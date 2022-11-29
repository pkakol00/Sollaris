#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include <queue>

class Vec3 {
public:
  double x, y, z;
};

class PlanetData{
public:
  double mass;
  double radious;
  double velocity;
  Vec3 colour;
  int planet_id;
};

class PlanetPosition{
public:
  std::queue<Vec3> positions;
  int planet_id;
};

#endif // __MATH_UTIL_H__