//
// Copyright (C) 2021 Marc Lorenz
//

#include <SFML/Graphics.hpp>
#include <chrono>
#include <sstream>
#include "Particle.h"
#include "Constants.h"
#include "Logger.h"
#include "SimulationLoader.h"

int main(int argc, char *argv[]) {
  /*
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " [Filename]" << std::endl;
    return 1;
  }
  */

  std::vector<Particle> particles = SimulationLoader::LoadSimulation("test.txt");  // argv[1]
  ASSERT(!particles.empty(), "No particles loaded");
  auto log = CLogger::GetLogger();

  sf::RenderWindow window(sf::VideoMode(constants::window_size, constants::window_size), "");

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

  while (window.isOpen()) {
    auto start = std::chrono::high_resolution_clock::now();

    for (auto &p: particles) {
      std::stringstream ss;
      if (p.getType() == Particle::ParticleType::FLUID) {
        ss << "Updated " << p;
        log->Log(ss.str());
      }
    }

    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
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
    /*
    window.clear();
    for (const auto &particle: particles) {
      particle.draw(window);
    }
    window.display();
*/
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, milli>(end - start);

    frame_counter++;
    log->Log(std::string("Rendered frame ") + to_string(frame_counter) + " in " + to_string(duration.count() / 1000) + " seconds.");

  }
  CLogger::exit();
  return 0;
}
