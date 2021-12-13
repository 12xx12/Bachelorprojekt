//
// Copyright (C) 2021 Marc Lorenz
//

#include <SFML/Graphics.hpp>
#include <chrono>
#include <sstream>
#include <thread>

#include "Constants.h"
#include "Logger.h"
#include "Particle.h"
#include "SimulationLoader.h"
#include "ParticleRenderer.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " [Filename]" << std::endl;
    return 1;
  }

  auto particles = SimulationLoader::LoadSimulation(argv[1]);
  ASSERT(!particles.empty(), "No particles loaded");
  auto log = CLogger::GetLogger();

  // logging stuff
  log->Log("");
  log->Log("");
  log->Log("");
  log->Log("Starting simulation");
  log->Log("");
  log->Log("");
  log->Log("");
  log->Log("Startup finished, rendering %d particles", particles.size());
  long long frame_counter = 0;

  // rendering stuff
  ParticleRenderer renderer(particles);
  renderer.Start();
  while (renderer.IsRunning()) {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto &p: particles) {
      std::stringstream ss;
      if (p.getType() == Particle::ParticleType::FLUID) {
        ss << "Updated " << p;
        log->Log(ss.str());
      }
    }

    std::for_each(particles.begin(), particles.end(), [&](Particle &p) {
      p.updateNeighbors(particles);
    });

    std::for_each(particles.begin(), particles.end(), [&](Particle &p) {
      p.updateDensity();
      p.updatePressure();
    });

    for (auto &particle: particles) {
      particle.updateVelocity(constants::time_step);
      particle.updatePosition(constants::time_step);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, milli>(end - start);

    frame_counter++;
    log->Log(std::string("Rendered frame ") + to_string(frame_counter) + " in "
                 + to_string(duration.count() / 1000) + " seconds.");

  }
  CLogger::exit();
  std::cout << "Exiting" << std::endl;

  return 0;
}
