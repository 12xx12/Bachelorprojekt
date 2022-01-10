//
// Created by marc_ on 13.12.2021.
//

#include "Utilities.h"

namespace Util {
std::string CurrentDateTime() {
  time_t now = time(nullptr);
  struct tm tstruct{};
  char buf[80];
  localtime_s(&tstruct, &now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}

double round(double value, int precision = 0) {
  float pow_10 = pow(10.0f, static_cast<float>(precision));
  return std::round(value * pow_10) / pow_10;
}
}
