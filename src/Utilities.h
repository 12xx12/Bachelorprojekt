//
// Created by marc_ on 10.11.2021.
//

#pragma once

#include <ctime>

#include "Logger.h"

namespace Util {
// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
extern std::string CurrentDateTime();
extern double round(double value, int precision);
}
