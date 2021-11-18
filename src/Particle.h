//
// Copyright (C) 2021 Marc Lorenz
//

#ifndef SRC_PARTICLE_H_
#define SRC_PARTICLE_H_

#include <ostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Vector.h"

class Particle {
 public:
  enum class ParticleType {
    NONE,
    BOUNDARY,
    FLUID
  };

  Particle(double x, double y, double density, ParticleType type);

  const Vector &getPos() const;
  const Vector &getVelocity() const;
  double getDensity() const;
  double getMass() const;
  double getPressure() const;
  ParticleType getType() const;
  int getId() const;

  void updateNeighbors(const std::vector<Particle> &particles);
  void updateDensity();
  void updatePressure();
  void updateVelocity(double time);
  void updatePosition(double time);

  std::vector<const Particle *> getNeighbours(const std::vector<Particle> &allParticles) const;
  double getKernelValue(const Particle &other) const;
  Vector getKernelDerivative(const Particle &other) const;

  void draw(sf::RenderWindow &window) const;
  friend std::ostream &operator<<(std::ostream &os, const Particle &particle);

 private:
  Vector _getPressureAcceleration() const;
  Vector _getViscosityAcceleration() const;

  Vector _pos;
  Vector _vel;
  double _density;
  double _baseDensity;
  double _pressure;
  double _mass;
  double _lastUpdate;
  ParticleType _type;
  std::vector<const Particle *> _neighbours;
  int _id;

  static int _idCounter;
};

#endif  // SRC_PARTICLE_H_
