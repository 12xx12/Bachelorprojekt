//
// Created by marc_ on 13.12.2021.
//

#pragma once

#include <fstream>

#include "Globals.h"
#include "Particle.h"

class ParticleAnalyzer {
 public:
  ParticleAnalyzer();
  ~ParticleAnalyzer();

  void Log(const ParticleVector & particles);
 private:
  static void StoreMap(const ParticleVector &particles);

  std::ofstream _densityFile;
  long long _iteration;
};
