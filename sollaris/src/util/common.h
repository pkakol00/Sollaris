#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include <queue>

class Vec3 {
public:
  double x, y, z;

  Vec3();
  Vec3(double, double, double);
  Vec3(const Vec3&);
  Vec3(Vec3&& b);
  ~Vec3();

  Vec3& operator=(const Vec3&);
  Vec3& operator=(Vec3&&);

  double length() const;
  Vec3 normalized() const;
  Vec3 squared() const;

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

  friend Vec3 operator+(Vec3, const Vec3&);
  friend Vec3 operator-(Vec3, const Vec3&);
  friend Vec3 operator*(Vec3, const Vec3&);
  friend Vec3 operator/(Vec3, const Vec3&);

  friend Vec3 operator+(Vec3, const double&);
  friend Vec3 operator-(Vec3, const double&);
  friend Vec3 operator*(Vec3, const double&);
  friend Vec3 operator/(Vec3, const double&);
};

struct PlanetData {
  double mass;
  double radious;
  Vec3 velocity;
  Vec3 colour;
  int planet_id;
};

struct PlanetPosition{
  std::queue<Vec3> positions;
  int planet_id;
};

#endif // __MATH_UTIL_H__
