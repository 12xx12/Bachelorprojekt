//
// Created by marc_ on 13.12.2021.
//

#include <thread>
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
  std::for_each(particles.begin(),
                particles.end(),
                [&](const Particle &particle) {
                  if (particle.getType() == Particle::Type::FLUID) {
                    numParticles++;
                    totalDensity += particle.getDensity();
                  }
                });
  _densityFile << _iteration << "\t" << totalDensity / numParticles << std::endl;
  _iteration++;
}

ParticleAnalyzer::~ParticleAnalyzer() {
  _densityFile.close();
}