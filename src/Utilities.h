//
// Created by marc_ on 10.11.2021.
//

#ifndef BACHELORPROJEKT_SRC_UTILITIES_H_
#define BACHELORPROJEKT_SRC_UTILITIES_H_

#include "Logger.h"

namespace Util {
// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string CurrentDateTime() {
  time_t now = time(NULL);
  struct tm tstruct;
  char buf[80];
  localtime_s(&tstruct, &now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}
}

#endif //BACHELORPROJEKT_SRC_UTILITIES_H_
