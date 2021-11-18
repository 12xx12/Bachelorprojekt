//
// Copyright (C) 2021 Marc Lorenz
//

#include <iostream>
#include <utility>
#include <string>
#include <sstream>

#define _USE_MATH_DEFINES

#include <cmath>

#include "Particle.h"
#include "Constants.h"

int Particle::_idCounter = 0;

Particle::Particle(double x, double y, double density,
                   Particle::ParticleType type) {
  _pos = Vector(x, y);
  _density = density;
  _type = type;
  _mass = _density * constants::volume;
  _baseDensity = _density;
  _vel = Vector(0, 0);
  _id = ++_idCounter;
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

Particle::ParticleType Particle::getType() const {
  return _type;
}

int Particle::getId() const {
  return _id;
}

void Particle::updateNeighbors(const std::vector<Particle> &particles) {
  if (_type != Particle::ParticleType::FLUID) {
    return;
  }
  _neighbours = getNeighbours(particles);
}

void Particle::updateDensity() {
  if (_type != Particle::ParticleType::FLUID) {
    return;
  }
  double density = 0;
  for (auto &neighbour: _neighbours) {
    density += neighbour->getMass() * this->getKernelValue(*neighbour);
  }
  _density = density;
}

void Particle::updatePressure() {
  if (_type != Particle::ParticleType::FLUID) {
    return;
  }
  _pressure = std::max(constants::stiffness * ((_density / _baseDensity) - 1), 0.0);
}

void Particle::updateVelocity(double time) {
  if (_type != Particle::ParticleType::FLUID) {
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
  if (_type != Particle::ParticleType::FLUID) {
    return;
  }
  _pos += _vel * time;
}

std::vector<const Particle *> Particle::getNeighbours(const std::vector<Particle> &allParticles) const {
  auto neighbours = std::vector<const Particle *>();
  neighbours.push_back(this);

  for (const auto &particle: allParticles) {
    if (particle._pos.distance(_pos) < constants::kernelSupport)
      neighbours.push_back(&particle);
  }
  return std::move(neighbours);
}

double Particle::getKernelValue(const Particle &other) const {
  auto distance = _pos.distance(other._pos) / constants::particleSize;
  constexpr double alpha = 5 / (14 * constants::pi * constants::volume);

  auto t1 = std::max(1 - distance, 0.0);
  auto t2 = std::max(2 - distance, 0.0);

  return alpha * (t2 * t2 * t2 - 4 * t1 * t1 * t1);
}

Vector Particle::getKernelDerivative(const Particle &other) const {
  if (_pos == other._pos) {
    return {0, 0};
  }

  auto distance = _pos.distance(other._pos) / constants::particleSize;
  constexpr double alpha = 5 / (14 * constants::pi * constants::volume);

  auto t1 = std::max(1 - distance, 0.0);
  auto t2 = std::max(2 - distance, 0.0);

  return alpha * ((_pos - other._pos) /
      (distance * constants::particleSize) *
      (-3 * t2 * t2 + 12 * t1 * t1));
}

void Particle::draw(sf::RenderWindow &window) const {
  sf::CircleShape circle(
      constants::particleRenderSize * constants::renderScale / 2);
  switch (_type) {
    case ParticleType::FLUID:circle.setFillColor(sf::Color::Blue);
      break;
    case ParticleType::BOUNDARY:circle.setFillColor(sf::Color::White);
      break;
    case ParticleType::NONE:circle.setFillColor(sf::Color::Red);
      break;
  }

  circle.setPosition(
      _pos.getX() * constants::renderScale + constants::window_size / 2,
      constants::window_size / 2 - _pos.getY() * constants::renderScale);
  window.draw(circle);
}

std::ostream &operator<<(std::ostream &os, const Particle &particle) {
  std::string type;
  switch (particle.getType()) {
    case Particle::ParticleType::BOUNDARY:type = "BOUNDARY";
      break;
    case Particle::ParticleType::FLUID:type = "FLUID";
      break;
    default:type = "UNKNOWN";
      break;
  }

  os << "Particle " << particle.getId() << ": " <<  type << " at " << particle.getPos() << " with velocity "
     << particle.getVelocity() << " and density " << particle.getDensity() << " and pressure " << particle.getPressure();
  return os;
}

Vector Particle::_getPressureAcceleration() const {
  constexpr double boundaryCorrection = 100.0;
  Vector pressureAcceleration(0, 0);
  for (const auto &neighbour: _neighbours) {

    switch (neighbour->getType()) {
      case Particle::ParticleType::FLUID: {
        pressureAcceleration -= neighbour->getMass() * ((getPressure() /
            pow(getDensity(),
                2)) +
            (neighbour->getPressure() /
                pow(neighbour->getDensity(),
                    2))) *
            getKernelDerivative(*neighbour);
        break;
      }
      case Particle::ParticleType::BOUNDARY: {
        pressureAcceleration -= boundaryCorrection * _mass *
            ((getPressure() /
                pow(getDensity(), 2)) +
                (getPressure() /
                    pow(getDensity(), 2))) *
            getKernelDerivative(*neighbour);
        break;
      }
      case Particle::ParticleType::NONE:ASSERT(false,
                                               "Particle is not fluid or boundary");
    }
  }
  return pressureAcceleration;
}

Vector Particle::_getViscosityAcceleration() const {
  Vector viscosityAcceleration(0, 0);
  for (const auto &neighbour: _neighbours) {
    auto t1 = (neighbour->getMass() / neighbour->getDensity());
    auto t2_upper =
        ((_vel - neighbour->getVelocity()) * (_pos - neighbour->getPos()));
    auto t2_lower = (_pos - neighbour->getPos()) * (_pos - neighbour->getPos())
        + 0.01 * constants::volume;
    auto t2 = t2_upper / t2_lower;
    viscosityAcceleration += t1 * t2 * getKernelDerivative(*neighbour);
  }
  viscosityAcceleration *= 2 * constants::friction;

  return viscosityAcceleration;
}
