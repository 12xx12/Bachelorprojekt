//
// Copyright (C) 2021 Marc Lorenz
//

#ifndef SRC_PARTICLE_H_
#define SRC_PARTICLE_H_

#include <ostream>
#include <vector>

#include "Vector.h"

class Particle {
 public:
  enum class ParticleType {
    NONE,
    BOUNDARY,
    FLUID
  };

  Particle(double x, double y, int density, ParticleType type);

  const Vector &getPos() const;
  const Vector &getVelocity() const;
  int getDensity() const;
  int getPressure() const;
  ParticleType getType() const;

  friend std::ostream &operator<<(std::ostream &os,
                                  const Particle &particle);
  std::vector<const Particle *> getNeighbours(const std::vector<Particle>
                                              &allParticles) const;

#ifdef BACHELOR_TEST
  bool operator==(const Particle &other) const {
    return this->_pos == other._pos && this->_density ==
        other._density && this->_type == other._type;
  }
#endif

 private:
  Vector _pos;
  Vector _vel;
  int _density;
  int _pressure;
  ParticleType _type;
};

#endif  // SRC_PARTICLE_H_
