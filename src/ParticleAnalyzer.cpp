//
// Created by marc_ on 13.12.2021.
//

#include <fstream>
#include <algorithm>
#include <filesystem>

#include "ParticleAnalyzer.h"
#include "Utilities.h"

ParticleAnalyzer::ParticleAnalyzer()
    : _iteration(0) {
  auto densityFileName = "densities/density_" + Util::CurrentDateTime() + ".txt";
  std::filesystem::create_directories("densities");
  std::replace(densityFileName.begin(), densityFileName.end(), ':', '_');
  _densityFile.open(densityFileName);
  ASSERT(_densityFile.is_open(), "Could not open density file");
}

void ParticleAnalyzer::Log(const ParticleVector &particles) {
  int numParticles = 0;
  double totalDensity = 0;
  std::for_each(particles.begin(), particles.end(),
  [&](const Particle &particle) {
    if (particle.getType() != Particle::Type::FLUID) {
      return;
    }
    numParticles++;
    totalDensity += particle.getDensity();
  });
  _densityFile << _iteration << "\t" << setprecision(10) << Util::round(totalDensity / numParticles, 10) << std::endl;

  // Creates a map of all particles in the simulation after 2000 iterations

  if (_iteration == 2000) {
    StoreMap(particles);
  }

  _iteration++;
}

void ParticleAnalyzer::StoreMap(const ParticleVector &particles) {
  std::ofstream mapFile;
  auto mapFileName = "maps/map_" + Util::CurrentDateTime() + ".txt";
  std::filesystem::create_directories("maps");
  std::replace(mapFileName.begin(), mapFileName.end(), ':', '_');
  mapFile.open(mapFileName);
  ASSERT(mapFile.is_open(), "Could not open map file");

  auto max = std::max_element(particles.begin(), particles.end(), [] (const Particle &a, const Particle &b) {
    if (b.getType() != Particle::Type::FLUID) {
      return false;
    }
    return a.getPos().getX() + a.getPos().getY() < b.getPos().getX() + b.getPos().getY();
  });

  auto min = std::min_element(particles.begin(), particles.end(), [] (const Particle &a, const Particle &b) {
    if (a.getType() != Particle::Type::FLUID) {
      return false;
    }
    return a.getPos().getX() + a.getPos().getY() < b.getPos().getX() + b.getPos().getY();
  });

  for (auto y = min->getPos().getY(); y < max->getPos().getY(); y += 0.1) {
    for (auto x = min->getPos().getX(); x < max->getPos().getX(); x += 0.1) {
      auto particle = Particle(x, y, 0, Particle::Type::FLUID);
      particle.updateNeighbors(particles);
      particle.updateDensity();
      auto density = particle.getDensity();
      mapFile << x << "\t" << y << "\t" << density << "\n";
    }
  }
  mapFile.close();
}

ParticleAnalyzer::~ParticleAnalyzer() {
  _densityFile.close();
}
