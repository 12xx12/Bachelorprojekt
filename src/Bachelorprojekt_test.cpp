//
// Created by marc_ on 09.11.2021.
//

#define BACHELOR_TEST

#include <gtest/gtest.h>
#include "Particle.h"

// testing neigbourhood search

// creating basic test set
// use density as index

auto testSet = std::vector<Particle>{
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

auto testSetWithBoundary = std::vector<Particle>{
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

// just test a empty neighbourhood and check if the particle is actually there
TEST(NeighbourSearch, EmptyNeighbourhood) {
  auto neighbourhood = std::vector<Particle>{};
  auto testParticle = Particle(0, 0, 42, Particle::ParticleType::FLUID);
  auto result = testParticle.getNeighbours(neighbourhood);
  EXPECT_EQ(result.size(), 1);
  EXPECT_EQ(result[0]->getDensity(), 42);
}

TEST(NeighbourSearch, BasicNeighbourhood) {
  auto testParticle = Particle(0, 0, 100, Particle::ParticleType::FLUID);
  auto result = testParticle.getNeighbours(testSet);
  EXPECT_EQ(result.size(), 10);
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
  auto result = testParticle.getNeighbours(testSetWithBoundary);
  EXPECT_EQ(result.size(), 6);
  EXPECT_EQ(result[0]->getDensity(), 8);
  EXPECT_EQ(result[0]->getPos(), Vector(0, -1.5));
  EXPECT_EQ(result[1]->getDensity(), 9);

}