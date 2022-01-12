//
// Copyright (C) 2021 Marc Lorenz
//

#define TEST_BUILD

#include <gtest/gtest.h>
#include "Particle.h"
#include "Constants.h"

// testing the vector class

TEST(VectorTest, EmptyConstructor) {
  auto v = Vector();
  EXPECT_EQ(v.getX(), 0);
  EXPECT_EQ(v.getY(), 0);
}

TEST(VectorTest, Constructor) {
  auto v = Vector(1, 2);
  EXPECT_EQ(v.getX(), 1);
  EXPECT_EQ(v.getY(), 2);
}

TEST(VectorTest, adding) {
  auto v1 = Vector(1, 2);
  auto v2 = Vector(3, 4);
  auto v3 = v1 + v2;
  EXPECT_EQ(v3.getX(), 4);
  EXPECT_EQ(v3.getY(), 6);
}

TEST(VectorTest, subtracting) {
  auto v1 = Vector(1, 2);
  auto v2 = Vector(3, 4);
  auto v3 = v1 - v2;
  EXPECT_EQ(v3.getX(), -2);
  EXPECT_EQ(v3.getY(), -2);
}

TEST(VectorTest, multiplying) {
  auto v1 = Vector(1, 2);
  auto v2 = v1 * 2;
  EXPECT_EQ(v2.getX(), 2);
  EXPECT_EQ(v2.getY(), 4);
}

TEST(VectorTest, dividing) {
  auto v1 = Vector(1, 2);
  auto v2 = v1 / 2;
  EXPECT_EQ(v2.getX(), 0.5);
  EXPECT_EQ(v2.getY(), 1);
}

TEST(VectorTest, distance) {
  auto v1 = Vector(1, 1);
  auto v2 = Vector(0, 0);
  EXPECT_DOUBLE_EQ(v1.distance(v2), sqrt(2));

  auto v3 = Vector(-1, -1);
  EXPECT_DOUBLE_EQ(v3.distance(v2), sqrt(2));

  auto v4 = Vector(1, 0);
  EXPECT_DOUBLE_EQ(v4.distance(v2), 1);

  auto v5 = Vector(0, 1);
  EXPECT_DOUBLE_EQ(v5.distance(v2), 1);

  auto v6 = Vector(-1, 0);
  EXPECT_DOUBLE_EQ(v6.distance(v2), 1);

  auto v7 = Vector(0, -1);
  EXPECT_DOUBLE_EQ(v7.distance(v2), 1);

  auto v8 = Vector(1, 1);
  EXPECT_DOUBLE_EQ(v8.distance(v2), sqrt(2));

  auto v9 = Vector(-1, -1);
  EXPECT_DOUBLE_EQ(v9.distance(v2), sqrt(2));

  auto v10 = Vector(2, -1);
  EXPECT_DOUBLE_EQ(v10.distance(v2), sqrt(5));

}

TEST(VectorTest, addingInPlace) {
  auto v1 = Vector(1, 2);
  auto v2 = Vector(3, 4);
  v1 += v2;
  EXPECT_EQ(v1.getX(), 4);
  EXPECT_EQ(v1.getY(), 6);
  EXPECT_EQ(v2.getX(), 3);
  EXPECT_EQ(v2.getY(), 4);
}

TEST(VectorTest, subtractinInPlace) {
  auto v1 = Vector(1, 2);
  auto v2 = Vector(3, 4);
  v1 -= v2;
  EXPECT_EQ(v1.getX(), -2);
  EXPECT_EQ(v1.getY(), -2);
  EXPECT_EQ(v2.getX(), 3);
  EXPECT_EQ(v2.getY(), 4);
}

TEST(VectorTest, multiplyInPlace) {
  auto v1 = Vector(1, 2);
  auto v2 = Vector(2, 3);
  auto res = v1 * v2;
  EXPECT_EQ(res, 8);
}

TEST(VectorTest, tensorProduct) {
  auto v1 = Vector(1, 2);
  auto v2 = Vector(3, 4);
  auto res = v1 % v2;
  EXPECT_EQ(res, Matrix(3, 6, 4, 8));
}

// testing neighbourhood search

// creating basic test set
// use density as index

namespace testSets {
auto basicSet = ParticleVector{
    Particle(-4.5, -4.5, 1, Particle::Type::FLUID),
    Particle(-4.5, -3, 2, Particle::Type::FLUID),
    Particle(-4.5, -1.5, 3, Particle::Type::FLUID),
    Particle(-4.5, 0, 4, Particle::Type::FLUID),
    Particle(-4.5, 1.5, 5, Particle::Type::FLUID),
    Particle(-4.5, 3, 6, Particle::Type::FLUID),
    Particle(-4.5, 4.5, 7, Particle::Type::FLUID),
    Particle(-3, -4.5, 8, Particle::Type::FLUID),
    Particle(-3, -3, 9, Particle::Type::FLUID),
    Particle(-3, -1.5, 10, Particle::Type::FLUID),
    Particle(-3, 0, 11, Particle::Type::FLUID),
    Particle(-3, 1.5, 12, Particle::Type::FLUID),
    Particle(-3, 3, 13, Particle::Type::FLUID),
    Particle(-3, 4.5, 14, Particle::Type::FLUID),
    Particle(-1.5, -4.5, 15, Particle::Type::FLUID),
    Particle(-1.5, -3, 16, Particle::Type::FLUID),
    Particle(-1.5, -1.5, 17, Particle::Type::FLUID),
    Particle(-1.5, 0, 18, Particle::Type::FLUID),
    Particle(-1.5, 1.5, 19, Particle::Type::FLUID),
    Particle(-1.5, 3, 20, Particle::Type::FLUID),
    Particle(-1.5, 4.5, 21, Particle::Type::FLUID),
    Particle(0, -4.5, 22, Particle::Type::FLUID),
    Particle(0, -3, 23, Particle::Type::FLUID),
    Particle(0, -1.5, 24, Particle::Type::FLUID),
    Particle(0, 0, 25, Particle::Type::FLUID),
    Particle(0, 1.5, 26, Particle::Type::FLUID),
    Particle(0, 3, 27, Particle::Type::FLUID),
    Particle(0, 4.5, 28, Particle::Type::FLUID),
    Particle(1.5, -4.5, 29, Particle::Type::FLUID),
    Particle(1.5, -3, 30, Particle::Type::FLUID),
    Particle(1.5, -1.5, 31, Particle::Type::FLUID),
    Particle(1.5, 0, 32, Particle::Type::FLUID),
    Particle(1.5, 1.5, 33, Particle::Type::FLUID),
    Particle(1.5, 3, 34, Particle::Type::FLUID),
    Particle(1.5, 4.5, 35, Particle::Type::FLUID),
    Particle(3, -4.5, 36, Particle::Type::FLUID),
    Particle(3, -3, 37, Particle::Type::FLUID),
    Particle(3, -1.5, 38, Particle::Type::FLUID),
    Particle(3, 0, 39, Particle::Type::FLUID),
    Particle(3, 1.5, 40, Particle::Type::FLUID),
    Particle(3, 3, 41, Particle::Type::FLUID),
    Particle(3, 4.5, 42, Particle::Type::FLUID),
    Particle(4.5, -4.5, 43, Particle::Type::FLUID),
    Particle(4.5, -3, 44, Particle::Type::FLUID),
    Particle(4.5, -1.5, 45, Particle::Type::FLUID),
    Particle(4.5, 0, 45, Particle::Type::FLUID),
    Particle(4.5, 1.5, 47, Particle::Type::FLUID),
    Particle(4.5, 3, 48, Particle::Type::FLUID),
    Particle(4.5, 4.5, 49, Particle::Type::FLUID),
};
}

// just test an empty neighbourhood and check if the particle is actually there
TEST(NeighbourSearch, EmptyNeighbourhood) {
  auto neighbourhood = ParticleVector{};
  auto testParticle = testSets::basicSet[24];
  auto result = testParticle.getNeighbours(neighbourhood);
  EXPECT_EQ(result.size(), 0);
}

TEST(NeighbourSearch, BasicNeighbourhood) {
  auto testParticle = testSets::basicSet[24];
  auto result = testParticle.getNeighbours(testSets::basicSet);
  EXPECT_EQ(result.size(), 9);

  for (const auto &particle: result) {
    EXPECT_EQ(particle->getType(), Particle::Type::FLUID);
  }

  EXPECT_EQ(result[0]->getDensity(), 17);
  EXPECT_EQ(result[0]->getPos(), Vector(-1.5, -1.5));
  EXPECT_EQ(result[1]->getDensity(), 18);
  EXPECT_EQ(result[1]->getPos(), Vector(-1.5, 0));
  EXPECT_EQ(result[2]->getDensity(), 19);
  EXPECT_EQ(result[2]->getPos(), Vector(-1.5, 1.5));
  EXPECT_EQ(result[3]->getDensity(), 24);
  EXPECT_EQ(result[3]->getPos(), Vector(0, -1.5));
  EXPECT_EQ(result[4]->getDensity(), 25);
  EXPECT_EQ(result[4]->getPos(), Vector(0, 0));
  EXPECT_EQ(result[5]->getDensity(), 26);
  EXPECT_EQ(result[5]->getPos(), Vector(0, 1.5));
  EXPECT_EQ(result[6]->getDensity(), 31);
  EXPECT_EQ(result[6]->getPos(), Vector(1.5, -1.5));
  EXPECT_EQ(result[7]->getDensity(), 32);
  EXPECT_EQ(result[7]->getPos(), Vector(1.5, 0));
  EXPECT_EQ(result[8]->getDensity(), 33);
  EXPECT_EQ(result[8]->getPos(), Vector(1.5, 1.5));
}

TEST(KenelFunction, compactTest) {
  auto testParticle = testSets::basicSet[24];
  for (const auto &neighbour: testSets::basicSet) {
    if (neighbour.getPos().distance(testParticle.getPos()) >= constants::kernelSupport) {
      EXPECT_NEAR(testParticle.getKernelValue(neighbour), 0, 0.0002);
    } else {
      EXPECT_GT(testParticle.getKernelValue(neighbour), 0);
    }
  }
}

TEST(KernelFunction, sum) {
  for (const auto &particle: testSets::basicSet) {
    double sum = 0;
    for (const auto &neighbour: testSets::basicSet) {
      sum += particle.getKernelValue(neighbour);
    }

    EXPECT_NEAR(sum, 1 / (constants::volume), 0.2);
  }
}

TEST(KernelFunction, reverse) {
  auto testParticle = testSets::basicSet[24];
  for (const auto &neighbour: testSets::basicSet) {
    EXPECT_NEAR(testParticle.getKernelValue(neighbour), neighbour.getKernelValue(testParticle), 0.1);
  }
}

TEST(KernelFunction, manualCalculation) {
  auto testParticle = testSets::basicSet[24];
  EXPECT_DOUBLE_EQ(testParticle.getKernelValue(testParticle), 4 * (5 / (14 * constants::pi * constants::volume)));
}

TEST(KernelDerivation, reverse) {
  for (const auto &testParticle: testSets::basicSet) {
    for (const auto &neighbour: testSets::basicSet) {
      auto w_i_j = testParticle.getKernelDerivative(neighbour);
      auto w_j_i = neighbour.getKernelDerivative(testParticle);
      EXPECT_NEAR(w_i_j.getX(), -w_j_i.getX(), 0.001);
      EXPECT_NEAR(w_i_j.getY(), -w_j_i.getY(), 0.001);
    }
  }
}

TEST(KerndelDerivation, sum) {
  for (const auto &testParticle: testSets::basicSet) {
    Vector sum;
    for (const auto &neighbour: testSets::basicSet) {
      sum += testParticle.getKernelDerivative(neighbour);
    }
    EXPECT_NEAR(sum.getX(), 0, 0.2);
    EXPECT_NEAR(sum.getY(), 0, 0.2);
  }
}

TEST(KernelDerivation, sameParticle) {
  for (const auto &testParticle: testSets::basicSet) {
    EXPECT_NEAR(testParticle.getKernelDerivative(testParticle).getX(), 0, 0.001);
    EXPECT_NEAR(testParticle.getKernelDerivative(testParticle).getY(), 0, 0.001);
  }
}

TEST(KernelDerivation, multiplication) {
  auto testParticle = testSets::basicSet[24];
  auto res = Matrix();
  for (const auto &neighbor: testParticle.getNeighbours(testSets::basicSet)) {
    auto pos = testParticle.getPos() - neighbor->getPos();
    auto derivative = testParticle.getKernelDerivative(*neighbor);
    res += pos % derivative;
  }
  auto TestMatrix = (-1 / constants::volume) * Matrix(1, 0, 0, 1);

  EXPECT_NEAR(res.x_1, TestMatrix.x_1, 0.01);
  EXPECT_NEAR(res.y_1, TestMatrix.y_1, 0.01);
  EXPECT_NEAR(res.x_2, TestMatrix.x_2, 0.01);
  EXPECT_NEAR(res.y_2, TestMatrix.y_2, 0.01);
}
