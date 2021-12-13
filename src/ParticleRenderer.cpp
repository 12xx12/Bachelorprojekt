//
// Created by marc_ on 09.12.2021.
//

#include <thread>

#include "ParticleRenderer.h"
#include "Constants.h"

ParticleRenderer::ParticleRenderer(ParticleVector &particles) :
    _particles(particles),
    _running(false)
{
}

void ParticleRenderer::Start() {
  if (_running) {
    EXIT("Trying to start a renderer thread while already running");
  }
  _running = true;
  _thread = std::thread([&]{
    sf::RenderWindow window(sf::VideoMode(constants::window_size, constants::window_size), "");
    while (_running) {
      window.clear();
      for (auto &particle : _particles) {
        sf::CircleShape circle(
            constants::particleRenderSize * constants::renderScale / 2);
        switch (particle.getType()) {
          case Particle::ParticleType::FLUID:circle.setFillColor(sf::Color::Blue);
            break;
          case Particle::ParticleType::BOUNDARY:circle.setFillColor(sf::Color::White);
            break;
          case Particle::ParticleType::NONE:circle.setFillColor(sf::Color::Red);
            break;
        }

        circle.setPosition(static_cast<float>(
                               particle.getPos().getX() * constants::renderScale
                                   + constants::window_size / 2.0),
                           static_cast<float>(constants::window_size / 2.0
                               - particle.getPos().getY() * constants::renderScale));
        window.draw(circle);
      }
      window.display();

      // Check for user interaction
      sf::Event event{};
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          _running = false;
      }
    }
    window.close();
  });
}

void ParticleRenderer::Stop() {
  if (!_running) {
    EXIT("Trying to stop a renderer not running!");
  }
  _running = false;
  _thread.join();
}
