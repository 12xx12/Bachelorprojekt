//
// Created by marc_ on 10.11.2021.
//

#pragma once

namespace constants {
constexpr double particleSize = 1.5;
constexpr double kernelSupport = 2 * particleSize;
constexpr double volume = particleSize * particleSize;
constexpr double gravity = 10.0;
constexpr double stiffness = 3000000.0;
constexpr double friction = 0.5;

constexpr int window_size = 1000.0;
constexpr float particleRenderSize = 1.5;

constexpr float time_step = 0.01;

constexpr double pi = 3.14159265358979323846;
}
