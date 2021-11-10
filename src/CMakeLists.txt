target_sources(
  ${CMAKE_PROJECT_NAME} PRIVATE
  Bachelorprojekt.cpp

  Particle.cpp
  Vector.cpp

  Particle.h
  Vector.h
  constants.h
)

target_sources(
  ${CMAKE_PROJECT_NAME}_test PRIVATE
  Bachelorprojekt_test.cpp

  Particle.cpp
  Vector.cpp

  Particle.h
  Vector.h
  constants.h
)

set(FOLDERS

  )

foreach(folder ${FOLDERS})
  add_subdirectory(${folder})
endforeach(folder)
