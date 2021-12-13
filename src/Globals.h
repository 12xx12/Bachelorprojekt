//
// Created by marc_ on 09.12.2021.
//

#pragma once

#include <vector>

#define ASSERT(condition, message) \
  do { \
      if (! (condition)) { \
          std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                    << " line " << __LINE__ << ": " << (message) << std::endl; \
          std::terminate(); \
      } \
  } while (false)

#define EXIT(message) \
    do { \
        std::cerr << "Error in " << __FILE__ << " line " << __LINE__ << ": " \
                  << (message) << std::endl; \
        std::terminate(); \
    } while (false)

class Particle;
using ParticleVector = std::vector<Particle>;
