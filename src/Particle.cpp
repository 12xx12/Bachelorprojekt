//
// Created by marc_ on 10.11.2021.
//

#include "Particle.h"
#include "constants.h"
#include <iostream>

Particle::Particle(double x, double y, int density, Particle::ParticleType type) {
	_pos = Vector(x, y);
	_density = density;
	_type = type;
}

const Vector &Particle::getPos() const {
	return _pos;
}

const Vector &Particle::getVelocity() const {
	return _vel;
}

int Particle::getDensity() const {
	return _density;
}

int Particle::getPressure() const {
	return _pressure;
}

Particle::ParticleType Particle::getType() const {
	return _type;
}

std::ostream &operator<<(std::ostream &os, const Particle &particle) {
	std::string type;
	switch (particle._type) {
		case Particle::ParticleType::BOUNDARY:
			type = "BOUNDARY";
			break;
		case Particle::ParticleType::FLUID:
			type = "FLUID";
			break;
		default:
			type = "UNKNOWN";
			break;
	}
	os << "Particle: " << type << " at " << particle._pos << " with velocity " << particle._vel << " and density " << particle._density << " and pressure " << particle._pressure;
	return os;
}

std::vector<const Particle *> Particle::getNeighbours(const std::vector<Particle> & allParticles) const
{
	auto neighbours = std::vector<const Particle *>();

	if (_type == ParticleType::FLUID) {
		neighbours.push_back(this);
	}

	for(const auto & particle : allParticles) {
        if (particle._type == ParticleType::FLUID && particle._pos.distance(_pos) < constants::distance)
            neighbours.push_back(& particle);
    }
	return std::move(neighbours);
}
