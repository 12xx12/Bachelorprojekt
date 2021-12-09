//
// Created by marc_ on 02.12.2021.
//

#ifndef BACHELORPROJEKT_SRC_SIMULATIONLOADER_H_
#define BACHELORPROJEKT_SRC_SIMULATIONLOADER_H_

#include <vector>
#include "Particle.h"

class SimulationLoader {
 public:
  static std::vector<Particle> LoadSimulation(std::string path);
};

#endif //BACHELORPROJEKT_SRC_SIMULATIONLOADER_H_
