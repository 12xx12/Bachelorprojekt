//
// Copyright (C) 2021 Marc Lorenz
//

#include <SFML/Graphics.hpp>
#include <chrono>
#include "Particle.h"
#include "Constants.h"
#include "Logger.h"

int main() {

  std::vector<Particle> particles{
      Particle(-5 * constants::place_dist, 0, 10, Particle::ParticleType::BOUNDARY),
      Particle(-5 * constants::place_dist, -1 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(-5 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(-4 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(-3 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(-2 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(-1 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(0, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(1 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(2 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(3 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(4 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(5 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(5 * constants::place_dist, -1 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(5 * constants::place_dist, 0, 10, Particle::ParticleType::BOUNDARY),

      Particle(0, 0, 1, Particle::ParticleType::FLUID),
  };

  auto log = CLogger::GetLogger();

  sf::RenderWindow window(sf::VideoMode(constants::window_size, constants::window_size), "");

  // lgging stuff
  log->Log("Startup finished, rendering %d particles", particles.size());
  long long frame_counter = 0;

  while (window.isOpen()) {
    auto start = std::chrono::high_resolution_clock::now();

    sf::Event event{};
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    for (auto &particle : particles) {
      particle.updateNeighbors(particles);
    }

    for (auto &particle : particles) {
      particle.updateDensity();
      particle.updatePressure();
    }

    for (auto &particle : particles) {
      particle.updateVelocity(constants::time_step);
      particle.updatePosition(constants::time_step);
    }

    window.clear();
    for (const auto & particle: particles) {
      particle.draw(window);
    }
    window.display();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, milli>(end - start);

    frame_counter++;
    log->Log(std::string("Rendered frame ") + to_string(frame_counter) + " in " + to_string(duration.count() / 1000) + " seconds.");

  }
  return 0;
}
