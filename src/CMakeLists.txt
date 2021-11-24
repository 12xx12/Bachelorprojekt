target_sources(
  ${CMAKE_PROJECT_NAME} PRIVATE
  Bachelorprojekt.cpp

  Particle.cpp
  Vector.cpp
  Logger.cpp
  Matrix.cpp

  Particle.h
  Vector.h
  Constants.h
  Logger.h
  Matrix.h
  Utilities.h
)

target_sources(
  ${CMAKE_PROJECT_NAME}_test PRIVATE
  Bachelorprojekt_test.cpp

  Particle.cpp
  Vector.cpp
  Logger.cpp
  Matrix.cpp

  Particle.h
  Vector.h
  Constants.h
  Logger.h
  Matrix.h
  Utilities.h
)

set(FOLDERS

  )

foreach(folder ${FOLDERS})
  add_subdirectory(${folder})
endforeach(folder)
