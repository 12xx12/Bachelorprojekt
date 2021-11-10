//
// Created by marc_ on 09.11.2021.
//

#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "Constants.h"

int main() {

  std::vector<Particle> particles{
      Particle(-2 * constants::place_dist, 0, 10, Particle::ParticleType::BOUNDARY),
      Particle(-2 * constants::place_dist, -1 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(-2 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(-1 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(0, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(1 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(2 * constants::place_dist, -2 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(2 * constants::place_dist, -1 * constants::place_dist, 10, Particle::ParticleType::BOUNDARY),
      Particle(2 * constants::place_dist, 0, 10, Particle::ParticleType::BOUNDARY),

      Particle(0, 0, 1, Particle::ParticleType::FLUID),
      Particle(1 * constants::place_dist, 0, 1, Particle::ParticleType::FLUID)
  };

  sf::RenderWindow window(sf::VideoMode(constants::window_size, constants::window_size), "");

  while (window.isOpen()) {
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
  }
  return 0;
}