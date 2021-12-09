

#include "SimulationLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Constants.h"

std::vector <Particle> SimulationLoader::LoadSimulation(std::string path) {
  std::vector <Particle> particles;
  std::cout << "Loading simulation from " << path << std::endl;
  std::ifstream file(path);

  if (!file.is_open()) {
    EXIT("Could not open file " + path);
  }

  std::vector <std::string> lines;
  size_t lineCount = 0;
  size_t lineLength = 0;
  {
    std::string line;
    while (std::getline(file, line)) {
      if (line[0] == '#')
        continue;
      lines.push_back(line);
      lineLength = std::max(lineLength, line.length());
      lineCount++;
    }
  }
  particles.reserve(lineCount * lineLength);

  ASSERT(lineCount > 0, "Got empty file");

  // center particles in the middle of the simulation

  double x = -static_cast<double>(lineLength / 2) * constants::particleSize;
  double y = static_cast<double>(lineCount / 2) * constants::particleSize;
  for (const auto & line : lines) {
    for (const auto & character : line) {
      // x = boundary, o = fluid, space = empty
      if (character == 'x') {
        particles.push_back(Particle(x , y , 2.1, Particle::ParticleType::BOUNDARY));
      } else if (character == 'o') {
        particles.push_back(Particle(x, y, 1.1, Particle::ParticleType::FLUID));
      } else if (character == ' ') {

      } else {
        std::cerr << "Unknown character " << character << " in line " << line << std::endl;
      }
      x += constants::particleSize;
    }
    x = -static_cast<double>(lineLength / 2) * constants::particleSize;
    y -= constants::particleSize;
  }
  std::cout << "Loaded " << particles.size() << " particles" << std::endl;
  return std::move(particles);
}
