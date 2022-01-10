cmake_minimum_required(VERSION 3.16)
project(Bachelorprojekt)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

enable_testing()

include("CMake/AddDependencies.cmake")
build_dependencies()

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(CMAKE_CXX_FLAGS_RELEASE  "-O2")
set(CMAKE_CXX_FLAGS_DEBUG   "-O2")

add_executable(${CMAKE_PROJECT_NAME}
    src/${CMAKE_PROJECT_NAME}.cpp
    src/Particle.cpp
    src/Vector.cpp
    src/Logger.cpp
    src/Matrix.cpp
    src/SimulationLoader.cpp
    src/ParticleRenderer.cpp
    src/ParticleAnalyzer.cpp

    src/Particle.h
    src/Vector.h
    src/Constants.h
    src/Logger.h
    src/Matrix.h
    src/Utilities.h
    src/SimulationLoader.h
    src/ParticleRenderer.h
    src/Globals.h
    src/ParticleAnalyzer.h
    src/Utilities.cpp
)

add_executable(${CMAKE_PROJECT_NAME}_test
    src/${CMAKE_PROJECT_NAME}_test.cpp
    src/Particle.cpp
    src/Vector.cpp
    src/Logger.cpp
    src/Matrix.cpp
    src/Utilities.cpp

    src/Particle.h
    src/Vector.h
    src/Constants.h
    src/Logger.h
    src/Matrix.h
    src/Utilities.h)

target_include_directories(
    ${CMAKE_PROJECT_NAME} SYSTEM PRIVATE
    lib/SFML/include
)

# Link dependencies as private:
target_link_libraries(
    ${CMAKE_PROJECT_NAME} PRIVATE
    sfml-graphics
)

target_include_directories(
    ${CMAKE_PROJECT_NAME}_test SYSTEM PRIVATE
    lib/googletest/googletest/include
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}_test PRIVATE
    gtest
    gtest_main
)

# Create a symbolic link from ${orig} to ${link}
# If the orig and link point to the same thing, does nothing (-> in-source build)
# If ${link} already exists, does nothing.
function(make_symlink orig link)
    # If both are the same, or link already exists, bail out:
    if ("${orig}" STREQUAL "${link}")
        return()
    endif()
    if (EXISTS ${link})
        return()
    endif()

    # Create the symlink (platform-dependent):
    message(STATUS "Creating symlink, orig = ${orig}; link = ${link}")
    if (CMAKE_HOST_UNIX)
        set(command ln -s ${orig} ${link})
    else()
        file(TO_NATIVE_PATH "${orig}" orig)
        file(TO_NATIVE_PATH "${link}" link)
        if (IS_DIRECTORY ${orig})
            set(command cmd.exe /c mklink /j ${link} ${orig})
        else()
            set(command cmd.exe /c mklink /h ${link} ${orig})
        endif()
    endif()

    execute_process(
            COMMAND ${command}
            RESULT_VARIABLE result
            ERROR_VARIABLE stderr
            OUTPUT_VARIABLE stdout
    )

    if (NOT ${result} EQUAL 0)
        message(FATAL_ERROR "Could not create symbolic link for: ${link} --> ${orig}: ${stderr} ${stdout}")
    endif()
endfunction(make_symlink)

make_symlink(${CMAKE_SOURCE_DIR}/simulations ${CMAKE_BINARY_DIR}/simulations)
