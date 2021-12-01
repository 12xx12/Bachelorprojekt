//
// Copyright (C) 2021 Marc Lorenz
//

#include <SFML/Graphics.hpp>
#include <chrono>
#include <sstream>
#include "Particle.h"
#include "Constants.h"
#include "Logger.h"

int main() {

  std::vector<Particle> particles{

        Particle(-5 * constants::particleSize, 10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, 9 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, 8 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, 7 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, 6 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, 5 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, 4 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, 3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, 2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, 1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, 0, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, -1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-4 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-3 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-2 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-1 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(0, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(1 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(2 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(3 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(4 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, -1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 0, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 4 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 5 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 6 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 7 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 8 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 9 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, 10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),

        Particle(-6 * constants::particleSize, 10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, 9 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, 8 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, 7 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, 6 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, 5 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, 4 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, 3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, 2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, 1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, 0, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, -1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-6 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-5 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-4 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-3 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-2 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(-1 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(0, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(1 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(2 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(3 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(4 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(5 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, -1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 0, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 4 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 5 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 6 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 7 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 8 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 9 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
        Particle(6 * constants::particleSize, 10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
/*
        Particle(-1 * constants::particleSize, 3 * constants::particleSize, 1, Particle::ParticleType::FLUID),
        Particle(-1 * constants::particleSize, 2 * constants::particleSize, 1, Particle::ParticleType::FLUID),
        Particle(-1 * constants::particleSize, 1 * constants::particleSize, 1, Particle::ParticleType::FLUID),
        Particle(0, 1 * constants::particleSize, 1, Particle::ParticleType::FLUID),
        Particle(0, 2 * constants::particleSize, 1, Particle::ParticleType::FLUID),
        Particle(0, 3 * constants::particleSize, 1, Particle::ParticleType::FLUID),
        Particle(1 * constants::particleSize, 3 * constants::particleSize, 1, Particle::ParticleType::FLUID),
        Particle(1 * constants::particleSize, 2 * constants::particleSize, 1, Particle::ParticleType::FLUID),
        Particle(1 * constants::particleSize, 1 * constants::particleSize, 1, Particle::ParticleType::FLUID),
*/
        // Particle(-1 * constants::particleSize, 2 * constants::particleSize, 1, Particle::ParticleType::FLUID),
        Particle(0, 2 * constants::particleSize, 1, Particle::ParticleType::FLUID),
        // Particle(1 * constants::particleSize, 2 * constants::particleSize, 1, Particle::ParticleType::FLUID),
/*
      Particle(-10 * constants::particleSize, 10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, 9 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, 8 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, 7 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, 6 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, 5 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, 4 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, 3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, 2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, 1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, 0, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, -1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, -4 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, -5 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, -6 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, -7 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, -8 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, -9 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-10 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-9 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-8 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-7 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-6 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-5 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-4 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-3 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-2 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(-1 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(0, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(1 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(2 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(3 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(4 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(5 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(6 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(7 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(8 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(9 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, -10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, -9 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, -8 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, -7 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, -6 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, -5 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, -4 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, -3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, -2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, -1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 0, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 1 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 2 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 3 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 4 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 5 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 6 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 7 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 8 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 9 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),
      Particle(10 * constants::particleSize, 10 * constants::particleSize, 5, Particle::ParticleType::BOUNDARY),

      Particle(-3 * constants::particleSize, -3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-2 * constants::particleSize, -3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-1 * constants::particleSize, -3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(0 * constants::particleSize, -3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(1 * constants::particleSize, -3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(2 * constants::particleSize, -3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(3 * constants::particleSize, -3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),

      Particle(-3 * constants::particleSize, -2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-2 * constants::particleSize, -2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-1 * constants::particleSize, -2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(0, -2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(1 * constants::particleSize, -2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(2 * constants::particleSize, -2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(3 * constants::particleSize, -2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),

      Particle(-3 * constants::particleSize, -1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-2 * constants::particleSize, -1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-1 * constants::particleSize, -1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(0, -1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(1 * constants::particleSize, -1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(2 * constants::particleSize, -1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(3 * constants::particleSize, -1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),

      Particle(-3 * constants::particleSize, 0, 1.1, Particle::ParticleType::FLUID),
      Particle(-2 * constants::particleSize, 0, 1.1, Particle::ParticleType::FLUID),
      Particle(-1 * constants::particleSize, 0, 1.1, Particle::ParticleType::FLUID),
      Particle(0, 0, 1.1, Particle::ParticleType::FLUID),
      Particle(1 * constants::particleSize, 0, 1.1, Particle::ParticleType::FLUID),
      Particle(2 * constants::particleSize, 0, 1.1, Particle::ParticleType::FLUID),
      Particle(3 * constants::particleSize, 0, 1.1, Particle::ParticleType::FLUID),

      Particle(-3 * constants::particleSize, 1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-2 * constants::particleSize, 1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-1 * constants::particleSize, 1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(0, 1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(1 * constants::particleSize, 1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(2 * constants::particleSize, 1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(3 * constants::particleSize, 1 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),

      Particle(-3 * constants::particleSize, 2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-2 * constants::particleSize, 2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-1 * constants::particleSize, 2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(0, 2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(1 * constants::particleSize, 2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(2 * constants::particleSize, 2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(3 * constants::particleSize, 2 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),

      Particle(-3 * constants::particleSize, 3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-2 * constants::particleSize, 3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(-1 * constants::particleSize, 3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(0, 3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(1 * constants::particleSize, 3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(2 * constants::particleSize, 3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
      Particle(3 * constants::particleSize, 3 * constants::particleSize, 1.1, Particle::ParticleType::FLUID),
*/
  };

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

    for (auto& p : particles) {
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

    std::for_each(particles.begin(), particles.end(), [&](Particle& p) {
      p.updateNeighbors(particles);
    });

    std::for_each(particles.begin(), particles.end(), [&](Particle& p) {
      p.updateDensity();
      p.updatePressure();
    });

    for (auto & particle : particles) {
      particle.updateVelocity(constants::time_step);
      particle.updatePosition(constants::time_step);
    }

    window.clear();
    for (const auto &particle: particles) {
      particle.draw(window);
    }
    window.display();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, milli>(end - start);

    frame_counter++;
    log->Log(std::string("Rendered frame ") + to_string(frame_counter) + " in " + to_string(duration.count() / 1000) + " seconds.");

  }
  CLogger::exit();
  return 0;
}
