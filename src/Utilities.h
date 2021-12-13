//
// Created by marc_ on 10.11.2021.
//

#pragma once

#include <ctime>

#include "Logger.h"

namespace Util {
// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
std::string CurrentDateTime() {
  time_t now = time(nullptr);
  struct tm tstruct{};
  char buf[80];
  localtime_s(&tstruct, &now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}
}
