//
// Created by marc_ on 02.12.2021.
//

#pragma once

#include <vector>
#include "Particle.h"

class SimulationLoader {
 public:
  static ParticleVector LoadSimulation(std::string path);
};

