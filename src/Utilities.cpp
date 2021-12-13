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
}