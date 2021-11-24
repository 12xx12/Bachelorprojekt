//
// Copyright (C) 2021 Marc Lorenz
//

// #define LOG_ENABLE

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "Logger.h"
#include "Utilities.h"
const char* CLogger::m_sFileName = "Log.txt";
CLogger *CLogger::m_pThis = nullptr;
ofstream CLogger::m_Logfile;

CLogger::CLogger() = default;
CLogger *CLogger::GetLogger() {
  if (m_pThis == nullptr) {
    m_pThis = new CLogger();
    m_Logfile.open(m_sFileName, ios::out | ios::trunc);
  }
  return m_pThis;
}

void CLogger::exit() {
  m_Logfile.flush();
  m_Logfile.close();
  delete [] m_pThis;
  auto currentPath = filesystem::current_path();
  try {
    auto currentTime = Util::CurrentDateTime();
    std::replace(currentTime.begin(), currentTime.end(), ':', '_');
    auto newPath = (string ("Log_") + currentTime + ".txt");
    filesystem::rename(currentPath / m_sFileName, currentPath / newPath);
  }
  catch (filesystem::filesystem_error &e) {
    cout << e.what() << endl;
  }
}

void CLogger::Log(const char *format, ...) {
  char *sMessage = nullptr;
  int nLength = 0;
  va_list args;
      va_start(args, format);
  //  Return the number of characters in the string referenced the list of arguments.
  // _vscprintf doesn't count terminating '\0' (that's why +1)
  nLength = _vscprintf(format, args) + 1;
  sMessage = new char[nLength];
  vsprintf_s(sMessage, nLength, format, args);
  m_Logfile << Util::CurrentDateTime() << ":\t";
  m_Logfile << sMessage << "\n";
#ifdef LOG_ENABLE
  cout << Util::CurrentDateTime() << ":\t";
  cout << sMessage << "\n";
#endif

      va_end(args);
  delete[] sMessage;
}

void CLogger::Log(const string &sMessage) {
  m_Logfile << Util::CurrentDateTime() << ":\t";
  m_Logfile << sMessage << "\n";
#ifdef LOG_ENABLE
  cout << Util::CurrentDateTime() << ":\t";
  cout << sMessage << "\n";
#endif
}

CLogger &CLogger::operator<<(const string &sMessage) {
  m_Logfile << Util::CurrentDateTime() << ":\t";
  m_Logfile << sMessage << "\n";
#ifdef LOG_ENABLE
  cout << "\n" << Util::CurrentDateTime() << ":\t";
  cout << sMessage << "\n";
#endif
  return *this;
}
