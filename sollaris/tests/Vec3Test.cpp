#include <iostream>
#include "gtest/gtest.h"
#include "../src/util/common.h"
#include <cmath>

TEST(Vec3Test, DefaultConstructor) {
  Vec3 tmp;
  EXPECT_EQ(0, tmp.x);
  EXPECT_EQ(0, tmp.y);
  EXPECT_EQ(0, tmp.z);
}

TEST(Vec3Test, Constructor) {
  double x = 10, y = 20, z = 30;
  Vec3 tmp {x, y, z};
  EXPECT_EQ(x, tmp.x);
  EXPECT_EQ(y, tmp.y);
  EXPECT_EQ(z, tmp.z);
}

TEST(Vec3Test, CopyConstructor) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {a};
  EXPECT_EQ(b.x, a.x);
  EXPECT_EQ(b.y, a.y);
  EXPECT_EQ(b.z, a.z);
}

TEST(Vec3Test, MoveConstructor) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {std::move(a)};
  EXPECT_EQ(0, a.x);
  EXPECT_EQ(0, a.y);
  EXPECT_EQ(0, a.z);
  EXPECT_EQ(x, b.x);
  EXPECT_EQ(y, b.y);
  EXPECT_EQ(z, b.z);
}

TEST(Vec3Test, CopyAssignment) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b;
  b = a;

  EXPECT_EQ(b.x, a.x);
  EXPECT_EQ(b.y, a.y);
  EXPECT_EQ(b.z, a.z);
}

TEST(Vec3Test, MoveAssignment) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b;
  b = std::move(a);

  EXPECT_EQ(0, a.x);
  EXPECT_EQ(0, a.y);
  EXPECT_EQ(0, a.z);
  EXPECT_EQ(x, b.x);
  EXPECT_EQ(y, b.y);
  EXPECT_EQ(z, b.z);
}

TEST(Vec3Test, length) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};

  double res = std::sqrt(x*x + y*y + z*z);

  EXPECT_NEAR(res, a.length(), 0.0001);
}

TEST(Vec3Test, squaredLength) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};

  double res = x*x + y*y + z*z;

  EXPECT_NEAR(res, a.squaredLength(), 0.0001);
}

TEST(Vec3Test, normalized) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 norm = a.normalized();

  EXPECT_NEAR(a.x / a.length(), norm.x, 0.0001);
  EXPECT_NEAR(a.y / a.length(), norm.y, 0.0001);
  EXPECT_NEAR(a.z / a.length(), norm.z, 0.0001);
}

TEST(Vec3Test, squared) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 squared = a.squared();

  EXPECT_NEAR(x * x, squared.x, 0.0001);
  EXPECT_NEAR(y * y, squared.y, 0.0001);
  EXPECT_NEAR(z * z, squared.z, 0.0001);
}

TEST(Vec3Test, PlusEqVec3) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {z, y, x};

  a += b;

  EXPECT_NEAR(x + z, a.x, 0.0001);
  EXPECT_NEAR(y + y, a.y, 0.0001);
  EXPECT_NEAR(z + x, a.z, 0.0001);
}

TEST(Vec3Test, MinusEqVec3) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {z, y, x};

  a -= b;

  EXPECT_NEAR(x - z, a.x, 0.0001);
  EXPECT_NEAR(y - y, a.y, 0.0001);
  EXPECT_NEAR(z - x, a.z, 0.0001);
}

TEST(Vec3Test, MulEqVec3) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {z, y, x};

  a *= b;

  EXPECT_NEAR(x * z, a.x, 0.0001);
  EXPECT_NEAR(y * y, a.y, 0.0001);
  EXPECT_NEAR(z * x, a.z, 0.0001);
}

TEST(Vec3Test, DivEqVec3) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {z, y, x};

  a /= b;

  EXPECT_NEAR(x / z, a.x, 0.0001);
  EXPECT_NEAR(y / y, a.y, 0.0001);
  EXPECT_NEAR(z / x, a.z, 0.0001);
}

TEST(Vec3Test, PlusEqDouble) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};

  a += 20;

  EXPECT_NEAR(x + 20, a.x, 0.0001);
  EXPECT_NEAR(y + 20, a.y, 0.0001);
  EXPECT_NEAR(z + 20, a.z, 0.0001);
}

TEST(Vec3Test, MinusEqDouble) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};

  a -= 20;

  EXPECT_NEAR(x - 20, a.x, 0.0001);
  EXPECT_NEAR(y - 20, a.y, 0.0001);
  EXPECT_NEAR(z - 20, a.z, 0.0001);
}

TEST(Vec3Test, MulEqDouble) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};

  a *= 20;

  EXPECT_NEAR(x * 20, a.x, 0.0001);
  EXPECT_NEAR(y * 20, a.y, 0.0001);
  EXPECT_NEAR(z * 20, a.z, 0.0001);
}

TEST(Vec3Test, DivEqDouble) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};

  a /= 20;

  EXPECT_NEAR(x / 20, a.x, 0.0001);
  EXPECT_NEAR(y / 20, a.y, 0.0001);
  EXPECT_NEAR(z / 20, a.z, 0.0001);
}

TEST(Vec3Test, UnaryPlus) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b = +a;

  EXPECT_NEAR(x, b.x, 0.0001);
  EXPECT_NEAR(y, b.y, 0.0001);
  EXPECT_NEAR(z, b.z, 0.0001);
}

TEST(Vec3Test, UnaryMinus) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b = -a;

  EXPECT_NEAR(-x, b.x, 0.0001);
  EXPECT_NEAR(-y, b.y, 0.0001);
  EXPECT_NEAR(-z, b.z, 0.0001);
}

TEST(Vec3Test, PlusVec3) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {z, y ,x};

  Vec3 c = a + b;

  EXPECT_NEAR(x + z, c.x, 0.0001);
  EXPECT_NEAR(y + y, c.y, 0.0001);
  EXPECT_NEAR(z + x, c.z, 0.0001);
}

TEST(Vec3Test, MinusVec3) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {z, y ,x};

  Vec3 c = a - b;

  EXPECT_NEAR(x - z, c.x, 0.0001);
  EXPECT_NEAR(y - y, c.y, 0.0001);
  EXPECT_NEAR(z - x, c.z, 0.0001);
}

TEST(Vec3Test, MulVec3) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {z, y ,x};

  Vec3 c = a * b;

  EXPECT_NEAR(x * z, c.x, 0.0001);
  EXPECT_NEAR(y * y, c.y, 0.0001);
  EXPECT_NEAR(z * x, c.z, 0.0001);
}

TEST(Vec3Test, DivVec3) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {z, y ,x};

  Vec3 c = a / b;

  EXPECT_NEAR(x / z, c.x, 0.0001);
  EXPECT_NEAR(y / y, c.y, 0.0001);
  EXPECT_NEAR(z / x, c.z, 0.0001);
}

TEST(Vec3Test, PlusDouble) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};

  Vec3 c = a + 40;

  EXPECT_NEAR(x + 40, c.x, 0.0001);
  EXPECT_NEAR(y + 40, c.y, 0.0001);
  EXPECT_NEAR(z + 40, c.z, 0.0001);
}

TEST(Vec3Test, MinusDouble) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};

  Vec3 c = a - 40;

  EXPECT_NEAR(x - 40, c.x, 0.0001);
  EXPECT_NEAR(y - 40, c.y, 0.0001);
  EXPECT_NEAR(z - 40, c.z, 0.0001);
}

TEST(Vec3Test, MulDouble) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {z, y ,x};

  Vec3 c = a * 40;

  EXPECT_NEAR(x * 40, c.x, 0.0001);
  EXPECT_NEAR(y * 40, c.y, 0.0001);
  EXPECT_NEAR(z * 40, c.z, 0.0001);
}

TEST(Vec3Test, DivDouble) {
  double x = 10, y = 20, z = 30;
  Vec3 a {x, y, z};
  Vec3 b {z, y ,x};

  Vec3 c = a / 40;

  EXPECT_NEAR(x / 40, c.x, 0.0001);
  EXPECT_NEAR(y / 40, c.y, 0.0001);
  EXPECT_NEAR(z / 40, c.z, 0.0001);
}
