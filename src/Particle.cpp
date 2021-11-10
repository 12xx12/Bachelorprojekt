//
// Copyright (C) 2021 Marc Lorenz
//

#include <iostream>
#include <utility>
#include <string>
#include <cassert>

#define _USE_MATH_DEFINES
#include <cmath>

#include "Particle.h"
#include "Constants.h"

Particle::Particle(double x, double y, int density,
                   Particle::ParticleType type) {
  _pos = Vector(x, y);
  _density = density;
  _type = type;
  _mass = _density * constants::volume;
  _restDensity = _density;
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

void Particle::updateNeighbors(const std::vector<Particle> &particles) {
  _neighbours = getNeighbours(particles);
  _boundaryNeighbours = _getBoundaryNeighbours(particles);
}

void Particle::updateDensity() {
  double density = 0;
  for (auto &neighbour: _neighbours) {
    density += neighbour->getMass() * this->getKernelValue(*neighbour);
  }
  _density = density;
}

void Particle::updatePressure() {
  _pressure = std::max(constants::stiffness * ((_density / _restDensity) - 1), 0.0);
}

void Particle::updateVelocity(double time) {
  Vector acceleration = Vector(0, 0);
  // non-pressure acceleration
  acceleration += Vector(0, -constants::gravity);
  acceleration += acceleration * constants::friction;
  // pressure acceleration
  acceleration += _getPressureAcceleration();
  _vel += acceleration * time;
}

void Particle::updatePosition(double time) {
  if (_type == Particle::ParticleType::FLUID) {
    _pos += _vel * time;
  }
}

std::vector<const Particle *> Particle::getNeighbours(
    const std::vector<Particle> &allParticles) const {
  auto neighbours = std::vector<const Particle *>();

  if (_type == ParticleType::FLUID) {
    neighbours.push_back(this);
  }

  for (const auto &particle: allParticles) {
    if (particle._type == ParticleType::FLUID &&
        particle._pos.distance(_pos) < constants::distance)
      neighbours.push_back(&particle);
  }
  return std::move(neighbours);
}

double Particle::getKernelValue(const Particle &other) const {
  auto distance = _pos.distance(other._pos) / constants::distance;
  constexpr double alpha = 5 / (14 * constants::pi * constants::distance * constants::distance);

  auto t1 = std::max(1 - distance, 0.0);
  auto t2 = std::max(2 - distance, 0.0);

  return alpha * (t2 * t2 * t2 - 4 * t1 * t1 * t1);
}

Vector Particle::getKernelDerivative(const Particle &other) const {
  if (_pos == other._pos) {
    return Vector(0, 0);
  }

  auto distance = _pos.distance(other._pos) / constants::distance;
  constexpr double alpha = 5 / (14 * constants::pi * constants::distance * constants::distance);

  auto t1 = std::max(1 - distance, 0.0);
  auto t2 = std::max(2 - distance, 0.0);

  return std::move(alpha * ((_pos - other._pos) / (distance * constants::distance) * (-3 * t2 * t2 + 12 * t1 * t1)));
}

void Particle::draw(sf::RenderWindow &window) const {
  sf::CircleShape circle(constants::particleRenderSize * constants::renderScale / 2);
  switch (_type) {
    case ParticleType::FLUID:circle.setFillColor(sf::Color::Blue);
      break;
    case ParticleType::BOUNDARY:circle.setFillColor(sf::Color::White);
      break;
    case ParticleType::NONE:circle.setFillColor(sf::Color::Red);
      break;
  }

  circle.setPosition(_pos.getX() * constants::renderScale + constants::window_size / 2,
                     constants::window_size / 2 - _pos.getY() * constants::renderScale);
  window.draw(circle);
}

std::ostream &operator<<(std::ostream &os, const Particle &particle) {
  std::string type;
  switch (particle._type) {
    case Particle::ParticleType::BOUNDARY: type = "BOUNDARY";
      break;
    case Particle::ParticleType::FLUID: type = "FLUID";
      break;
    default: type = "UNKNOWN";
      break;
  }
  os << "Particle: " << type << " at " << particle._pos << " with velocity " <<
     particle._vel << " and density " << particle._density;
  return os;
}

Vector Particle::_getPressureAcceleration() const {
  Vector pressureAcceleration(0, 0);
  for (const auto & neighbour: _neighbours) {
    pressureAcceleration -= neighbour->getMass() *
        ((getPressure() / pow(getDensity(), 2)) +
        (neighbour->getPressure() / pow(neighbour->getDensity(), 2))) * getKernelDerivative(*neighbour);
  }

  for (const auto & neighbour: _boundaryNeighbours) {
    pressureAcceleration -= neighbour->getMass() *
        ((getPressure() / pow(getDensity(), 2)) +
        (getPressure() / pow(getDensity(), 2))) * getKernelDerivative(*neighbour);
  }

  return std::move(pressureAcceleration);
}

std::vector<const Particle *> Particle::_getBoundaryNeighbours(const std::vector<Particle> &allParticles) const {
  auto neighbours = std::vector<const Particle *>();

  if (_type == ParticleType::BOUNDARY) {
    neighbours.push_back(this);
  }

  for (const auto &particle: allParticles) {
    if (particle._type == ParticleType::BOUNDARY &&
        particle._pos.distance(_pos) < constants::distance)
      neighbours.push_back(&particle);
  }
  return std::move(neighbours);
}
