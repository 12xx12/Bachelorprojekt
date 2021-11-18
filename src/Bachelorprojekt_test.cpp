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
}

TEST(VectorTest, addingInPlace) {
  auto v1 = Vector(1, 2);
  auto v2 = Vector(3, 4);
  v1 += v2;
  EXPECT_EQ(v1.getX(), 4);
  EXPECT_EQ(v1.getY(), 6);
}

TEST(VectorTest, subtractinInPlace) {
  auto v1 = Vector(1, 2);
  auto v2 = Vector(3, 4);
  v1 -= v2;
  EXPECT_EQ(v1.getX(), -2);
  EXPECT_EQ(v1.getY(), -2);
}

TEST(VectorTest, multiplyInPlace) {
  auto v1 = Vector(1, 2);
  auto v2 = Vector(2, 3);
  auto res = v1 * v2;
  EXPECT_EQ(res, 8);
}

// testing neighbourhood search

// creating basic test set
// use density as index

namespace testSets {
auto basicSet = std::vector<Particle>{
    Particle(-3, -3, 1, Particle::ParticleType::FLUID),
    Particle(-1.5, -3, 2, Particle::ParticleType::FLUID),
    Particle(0, -3, 3, Particle::ParticleType::FLUID),
    Particle(1.5, -3, 4, Particle::ParticleType::FLUID),
    Particle(3, -3, 5, Particle::ParticleType::FLUID),
    Particle(-3, -1.5, 6, Particle::ParticleType::FLUID),
    Particle(-1.5, -1.5, 7, Particle::ParticleType::FLUID),
    Particle(0, -1.5, 8, Particle::ParticleType::FLUID),
    Particle(1.5, -1.5, 9, Particle::ParticleType::FLUID),
    Particle(3, -1.5, 10, Particle::ParticleType::FLUID),
    Particle(-3, 0, 11, Particle::ParticleType::FLUID),
    Particle(-1.5, 0, 12, Particle::ParticleType::FLUID),
    Particle(0, 0, 13, Particle::ParticleType::FLUID),
    Particle(1.5, 0, 14, Particle::ParticleType::FLUID),
    Particle(3, 0, 15, Particle::ParticleType::FLUID),
    Particle(-3, 1.5, 16, Particle::ParticleType::FLUID),
    Particle(-1.5, 1.5, 17, Particle::ParticleType::FLUID),
    Particle(0, 1.5, 18, Particle::ParticleType::FLUID),
    Particle(1.5, 1.5, 19, Particle::ParticleType::FLUID),
    Particle(3, 1.5, 20, Particle::ParticleType::FLUID),
    Particle(-3, 3, 21, Particle::ParticleType::FLUID),
    Particle(-1.5, 3, 22, Particle::ParticleType::FLUID),
    Particle(0, 3, 23, Particle::ParticleType::FLUID),
    Particle(1.5, 3, 24, Particle::ParticleType::FLUID),
    Particle(3, 3, 25, Particle::ParticleType::FLUID)
};

auto withBoundaryParticles = std::vector<Particle>{
    Particle(-3, -3, 1, Particle::ParticleType::FLUID),
    Particle(-1.5, -3, 2, Particle::ParticleType::BOUNDARY),
    Particle(0, -3, 3, Particle::ParticleType::FLUID),
    Particle(1.5, -3, 4, Particle::ParticleType::FLUID),
    Particle(3, -3, 5, Particle::ParticleType::FLUID),
    Particle(-3, -1.5, 6, Particle::ParticleType::FLUID),
    Particle(-1.5, -1.5, 7, Particle::ParticleType::BOUNDARY),
    Particle(0, -1.5, 8, Particle::ParticleType::FLUID),
    Particle(1.5, -1.5, 9, Particle::ParticleType::FLUID),
    Particle(3, -1.5, 10, Particle::ParticleType::FLUID),
    Particle(-3, 0, 11, Particle::ParticleType::FLUID),
    Particle(-1.5, 0, 12, Particle::ParticleType::BOUNDARY),
    Particle(0, 0, 13, Particle::ParticleType::FLUID),
    Particle(1.5, 0, 14, Particle::ParticleType::FLUID),
    Particle(3, 0, 15, Particle::ParticleType::FLUID),
    Particle(-3, 1.5, 16, Particle::ParticleType::FLUID),
    Particle(-1.5, 1.5, 17, Particle::ParticleType::BOUNDARY),
    Particle(0, 1.5, 18, Particle::ParticleType::FLUID),
    Particle(1.5, 1.5, 19, Particle::ParticleType::FLUID),
    Particle(3, 1.5, 20, Particle::ParticleType::FLUID),
    Particle(-3, 3, 21, Particle::ParticleType::FLUID),
    Particle(-1.5, 3, 22, Particle::ParticleType::FLUID),
    Particle(0, 3, 23, Particle::ParticleType::FLUID),
    Particle(1.5, 3, 24, Particle::ParticleType::FLUID),
    Particle(3, 3, 25, Particle::ParticleType::FLUID)
};
}

// just test an empty neighbourhood and check if the particle is actually there
TEST(NeighbourSearch, EmptyNeighbourhood) {
  auto neighbourhood = std::vector<Particle>{};
  auto testParticle = Particle(0, 0, 42, Particle::ParticleType::FLUID);
  auto result = testParticle.getNeighbours(neighbourhood);
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0]->getDensity(), 42);
}

TEST(NeighbourSearch, BasicNeighbourhood) {
  auto testParticle = Particle(0, 0, 100, Particle::ParticleType::FLUID);
  auto result = testParticle.getNeighbours(testSets::basicSet);
  EXPECT_EQ(result.size(), 10);

  for (const auto & particle : result) {
    EXPECT_EQ(particle->getType(), Particle::ParticleType::FLUID);
  }

  EXPECT_EQ(result[0]->getDensity(), 100);
  EXPECT_EQ(result[1]->getDensity(), 7);
  EXPECT_EQ(result[1]->getPos(), Vector(-1.5, -1.5));
  EXPECT_EQ(result[2]->getDensity(), 8);
  EXPECT_EQ(result[2]->getPos(), Vector(0, -1.5));
  EXPECT_EQ(result[3]->getDensity(), 9);
  EXPECT_EQ(result[3]->getPos(), Vector(1.5, -1.5));
  EXPECT_EQ(result[4]->getDensity(), 12);
  EXPECT_EQ(result[4]->getPos(), Vector(-1.5, 0));
  EXPECT_EQ(result[5]->getDensity(), 13);
  EXPECT_EQ(result[5]->getPos(), Vector(0, 0));
  EXPECT_EQ(result[6]->getDensity(), 14);
  EXPECT_EQ(result[6]->getPos(), Vector(1.5, 0));
  EXPECT_EQ(result[7]->getDensity(), 17);
  EXPECT_EQ(result[7]->getPos(), Vector(-1.5, 1.5));
  EXPECT_EQ(result[8]->getDensity(), 18);
  EXPECT_EQ(result[8]->getPos(), Vector(0, 1.5));
  EXPECT_EQ(result[9]->getDensity(), 19);
  EXPECT_EQ(result[9]->getPos(), Vector(1.5, 1.5));
}

TEST(NeighbourSearch, NoBoundaryParticleEmpty) {
  auto neighbourhood = std::vector<Particle>{};
  auto testParticle = Particle(0, 0, 42, Particle::ParticleType::BOUNDARY);
  auto result = testParticle.getNeighbours(neighbourhood);
  EXPECT_EQ(result.size(), 0);
}

TEST(NeighbourSearch, NoBoundaryParticleSet) {
  auto testParticle = Particle(0, 0, 42, Particle::ParticleType::BOUNDARY);
  auto result = testParticle.getNeighbours(testSets::withBoundaryParticles);
  EXPECT_EQ(result.size(), 6);
  EXPECT_EQ(result[0]->getDensity(), 8);
  EXPECT_EQ(result[0]->getPos(), Vector(0, -1.5));
  EXPECT_EQ(result[1]->getDensity(), 9);
  EXPECT_EQ(result[1]->getPos(), Vector(1.5, -1.5));
  EXPECT_EQ(result[2]->getDensity(), 13);
  EXPECT_EQ(result[2]->getPos(), Vector(0, 0));
  EXPECT_EQ(result[3]->getDensity(), 14);
  EXPECT_EQ(result[3]->getPos(), Vector(1.5, 0));
  EXPECT_EQ(result[4]->getDensity(), 18);
  EXPECT_EQ(result[4]->getPos(), Vector(0, 1.5));
  EXPECT_EQ(result[5]->getDensity(), 19);
  EXPECT_EQ(result[5]->getPos(), Vector(1.5, 1.5));
}

TEST(KenelFunction, compactTest) {
  auto testParticle = Particle(0, 0, 42, Particle::ParticleType::FLUID);
  for (const auto &neighbour: testSets::basicSet) {
    if (neighbour.getPos().distance(testParticle.getPos()) > constants::particleSize) {
      EXPECT_NEAR(testParticle.getKernelValue(neighbour), 0, 0.02);
    } else {
      EXPECT_GT(testParticle.getKernelValue(neighbour), 0);
    }
  }
}

TEST(KernelFunction, sum) {
  auto testParticle = Particle(0, 0, 42, Particle::ParticleType::FLUID);
  double sum = 0;
  for (const auto &neighbour: testSets::basicSet) {
    sum += testParticle.getKernelValue(neighbour);
  }

  EXPECT_NEAR(sum, 1 / (constants::particleSize * constants::particleSize), 0.1);
}

TEST(KernelFunction, reverse) {
  auto testParticle = Particle(0, 0, 42, Particle::ParticleType::FLUID);
  for (const auto &neighbour: testSets::basicSet) {
    EXPECT_NEAR(testParticle.getKernelValue(neighbour), neighbour.getKernelValue(testParticle), 0.1);
  }
}

TEST(KerndelDerivation, sum) {
  auto testParticle = Particle(0, 0, 42, Particle::ParticleType::FLUID);
  auto sum = Vector();
  for (const auto &neighbour: testSets::basicSet) {
    sum += testParticle.getKernelDerivative(neighbour);
  }

  EXPECT_NEAR(sum.getX(), 0, 0.001);
  EXPECT_NEAR(sum.getY(), 0, 0.001);
}
