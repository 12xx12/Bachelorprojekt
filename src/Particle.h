//
// Copyright (C) 2021 Marc Lorenz
//

#pragma once

#include <ostream>

#include "Globals.h"
#include "Vector.h"

class Particle {
 public:
  enum class Type {
    NONE,
    BOUNDARY,
    FLUID
  };

  Particle(double x, double y, double density, Type type);

  const Vector &getPos() const;
  const Vector &getVelocity() const;
  double getDensity() const;
  double getMass() const;
  double getPressure() const;
  Type getType() const;
  int getId() const;

  void updateNeighbors(const ParticleVector &particles);
  void updateDensity();
  void updatePressure();
  void updateVelocity(double time);
  void updatePosition(double time);

  std::vector<const Particle *> getNeighbours(const ParticleVector &allParticles) const;
  double getKernelValue(const Particle &other) const;
  Vector getKernelDerivative(const Particle &other) const;

  friend std::ostream &operator<<(std::ostream &os, const Particle &particle);
  void SetPos(const Vector &pos);

 private:
  Vector _getPressureAcceleration() const;
  Vector _getViscosityAcceleration() const;

  Vector _pos;
  Vector _vel;
  double _density;
  double _baseDensity;
  double _pressure{};
  double _mass;
  double _lastUpdate{};
  Type _type;
  std::vector<const Particle *> _neighbours;
  int _id;

  static int _idCounter;
};
