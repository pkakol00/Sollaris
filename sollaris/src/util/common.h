#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include <queue>

class Vec3 {
public:
  double x, y, z;

  double length() const;
  Vec3 normalized() const;

  Vec3& operator+=(const Vec3&);
  Vec3& operator-=(const Vec3&);
  Vec3& operator*=(const Vec3&);
  Vec3& operator/=(const Vec3&);

  Vec3& operator+=(const double&);
  Vec3& operator-=(const double&);
  Vec3& operator*=(const double&);
  Vec3& operator/=(const double&);

  Vec3 operator+() const;
  Vec3 operator-() const;

  friend Vec3 square(Vec3);

  friend Vec3 operator+(Vec3, const Vec3&);
  friend Vec3 operator-(Vec3, const Vec3&);
  friend Vec3 operator*(Vec3, const Vec3&);
  friend Vec3 operator/(Vec3, const Vec3&);

  friend Vec3 operator+(Vec3, const double&);
  friend Vec3 operator-(Vec3, const double&);
  friend Vec3 operator*(Vec3, const double&);
  friend Vec3 operator/(Vec3, const double&);
};

class PlanetData{
  double mass;
  double radious;
  double velocity;
  Vec3 colour;
  int planet_id;
};

class PlanetPosition{
  std::queue<Vec3> positions;
  int planet_id;
};

#endif // __MATH_UTIL_H__
