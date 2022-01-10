//
// Copyright (C) 2021 Marc Lorenz
//

#include <chrono>
#include <sstream>
#include <thread>

#include "Constants.h"
#include "Logger.h"
#include "Particle.h"
#include "SimulationLoader.h"
#include "ParticleRenderer.h"
#include "ParticleAnalyzer.h"

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " [Filename]" << std::endl;
    return 1;
  }

  auto log = CLogger::GetLogger();
  // logging stuff
  log->Log("");
  log->Log("");
  log->Log("");
  log->Log("Starting simulation");
  log->Log("");
  log->Log("");
  log->Log("");

  auto particles = SimulationLoader::LoadSimulation(argv[1]);

  ASSERT(!particles.empty(), "No particles loaded");

  log->Log("Startup finished, rendering %d particles", particles.size());
  long long frame_counter = 0;

  // rendering stuff
  ParticleRenderer renderer(particles);

  // archiving the average density
  ParticleAnalyzer analyzer;

  while (renderer.IsRunning()) {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto &p: particles) {
      std::stringstream ss;
      if (p.getType() == Particle::Type::FLUID) {
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

    if (frame_counter % constants::analyze_every_n_frames == 0) {
      analyzer.Log(particles);
    }
  }
  CLogger::exit();
  std::cout << "Exiting" << std::endl;

  return 0;
}
