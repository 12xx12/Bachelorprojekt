//
// Created by marc_ on 09.12.2021.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <thread>
#include "Particle.h"

class ParticleRenderer {
 public:
  ParticleRenderer(ParticleVector &particles);
  void Start();
  bool IsRunning() { return _running; }
 private:

  ParticleVector &_particles;
  std::thread _thread;
  bool _running;

};
