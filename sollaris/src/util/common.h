#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include <deque>
#include <string>

class Serializable{
public:
  virtual Serializable* deserialize(const std::string& data) = 0;
  virtual std::string& serialize() = 0;
  virtual ~Serializable() = default;
};

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

class PlanetData : public Serializable{
public:
  double mass, radious;
  int planet_id;
  Vec3 velocity, colour;
  PlanetData* deserialize(const std::string& data);
  std::string& serialize();
  PlanetData();
  PlanetData(double, double, Vec3, Vec3, int);
  ~PlanetData();
};

class PlanetPosition{
public:
  std::deque<Vec3> positions;
  int planet_id;
  PlanetPosition* deserialize(const std::string& data);
  std::string& serialize();
  PlanetPosition(std::deque<Vec3> positions, int planet_id);
  ~PlanetPosition();
};

#endif // __MATH_UTIL_H__