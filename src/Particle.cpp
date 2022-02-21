//
// Copyright (C) 2021 Marc Lorenz
//

#include <iostream>
#include <utility>
#include <string>

#include <cmath>
#include <algorithm>

#include "Particle.h"
#include "Constants.h"

int Particle::_idCounter = 0;

Particle::Particle(double x, double y, double density,
                   Particle::Type type) {
  _pos = Vector(x, y);
  _density = density;
  _type = type;
  _mass = _density * constants::volume;
  _baseDensity = _density;
  _vel = Vector(0, 0);
  _id = ++_idCounter;
  _pressure = 0;
}
void Particle::SetPos(const Vector &pos) {
  _pos = pos;
}

const Vector &Particle::getPos() const {
  return _pos;
}

const Vector &Particle::getVelocity() const {
  return _vel;
}

double Particle::getDensity() const {
  return _density;
}

double Particle::getMass() const {
  return _mass;
}

double Particle::getPressure() const {
  return _pressure;
}

Particle::Type Particle::getType() const {
  return _type;
}

int Particle::getId() const {
  return _id;
}

void Particle::updateNeighbors(const ParticleVector &particles) {
  _neighbours = getNeighbours(particles);
  // ASSERT(!_neighbours.empty(), "No neighbours");
}

void Particle::updateDensity() {
  if (_type != Particle::Type::FLUID) {
    return;
  }
  double density = 0.0;
  for (auto &neighbour: _neighbours) {
    density += neighbour->getMass() * getKernelValue(*neighbour);
  }
  ASSERT(density >= 0, "Density is negative");
  _density = density;
}

void Particle::updatePressure() {
  _pressure = std::max<double>(constants::stiffness * ((_density / _baseDensity) - 1), 0.0);
}

void Particle::updateVelocity(double time) {
  if (_type != Particle::Type::FLUID) {
    return;
  }
  Vector acceleration = Vector(0, 0);
  // non-pressure acceleration
  acceleration += Vector(0, -constants::gravity);
  acceleration += _getViscosityAcceleration();
  // pressure acceleration
  acceleration += _getPressureAcceleration();
  _vel += acceleration * time;
}

void Particle::updatePosition(double time) {
  if (_type != Particle::Type::FLUID) {
    return;
  }
  _pos += _vel * time;
}

std::vector<const Particle *> Particle::getNeighbours(const ParticleVector &allParticles) const {
  auto neighbours = std::vector<const Particle *>();

  std::for_each(allParticles.begin(), allParticles.end(), [&](const Particle &particle) {
    if (particle._pos.distance(_pos) < constants::kernelSupport)
      neighbours.push_back(&particle);
  });
  return std::move(neighbours);
}

double Particle::getKernelValue(const Particle &other) const {
  auto distance = other._pos.distance(_pos) / constants::particleSize;
  constexpr double alpha = 5 / (14 * constants::pi * constants::volume);

  auto t1 = std::max(1.0 - distance, 0.0);
  auto t2 = std::max(2.0 - distance, 0.0);

  return alpha * (pow(t2, 3) - 4 * pow(t1, 3));
}

Vector Particle::getKernelDerivative(const Particle &other) const {
  if (_id == other.getId()) {
    return {};
  }

  auto distance = other._pos.distance(_pos) / constants::particleSize;
  constexpr double alpha = 5 / (14 * constants::pi * constants::volume);

  if (distance >= 2)
  {
    return {};
  }

  double res;

  if (1 <= distance && distance < 2)
  {
    res = -3 * pow(2 - distance, 2);
  }
  if (0 <= distance && distance < 1)
  {
    res = -3 * pow(2 - distance, 2) + 12 * pow(1 - distance, 2);
  }

  return alpha * ((_pos - other.getPos()) / (distance * constants::particleSize * constants::particleSize)) * res;
}

std::ostream &operator<<(std::ostream &os, const Particle &particle) {
  std::string type;
  switch (particle.getType()) {
    case Particle::Type::BOUNDARY:type = "BOUNDARY";
      break;
    case Particle::Type::FLUID:type = "FLUID";
      break;
    default:type = "UNKNOWN";
      break;
  }

  os << "Particle " << particle.getId() << ": " << type << " at "
     << particle.getPos() << " with velocity "
     << particle.getVelocity() << " and density " << particle.getDensity()
     << " and pressure " << particle.getPressure();
  return os;
}

Vector Particle::_getPressureAcceleration() const {
  Vector solidAcceleration;
  Vector fluidAcceleration;
  for (const auto &neighbour: _neighbours) {
    switch (neighbour->getType()) {
      case Particle::Type::FLUID: {
        fluidAcceleration += ((_pressure / pow(_density, 2)) + (neighbour->getPressure() / pow(neighbour->getDensity(), 2))) * getKernelDerivative(*neighbour);
        break;
      }
      case Particle::Type::BOUNDARY: {
        solidAcceleration += ((_pressure / pow(_density, 2)) + (_pressure / pow(_density, 2))) * getKernelDerivative(*neighbour);
        break;
      }
      case Particle::Type::NONE:ASSERT(false, "Particle is not fluid or boundary");
    }
  }

  return -_mass * (fluidAcceleration + solidAcceleration);
}

Vector Particle::_getViscosityAcceleration() const {
  constexpr double boundaryCorrection = 1.5;
  Vector viscosityAcceleration(0, 0);
  for (const auto &neighbour: _neighbours) {
    auto t1 = (neighbour->getMass() / neighbour->getDensity());
    auto t2_upper = ((_vel - neighbour->getVelocity()) * (_pos - neighbour->getPos()));
    auto t2_lower = pow((_pos - neighbour->getPos()).distance({}), 2) + 0.01 * constants::volume;
    auto t2 = t2_upper / t2_lower;
    viscosityAcceleration += t1 * t2 * getKernelDerivative(*neighbour) * ((neighbour->getType() == Type::FLUID) ? 1 : boundaryCorrection);
  }
  viscosityAcceleration *= 2 * constants::friction;
  return viscosityAcceleration;
}
