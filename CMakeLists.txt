cmake_minimum_required(VERSION 3.16)
project(Bachelorprojekt)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)
# set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

enable_testing()

include("CMake/AddDependencies.cmake")
build_dependencies()

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(${CMAKE_PROJECT_NAME} src/${CMAKE_PROJECT_NAME}.cpp)
add_executable(${CMAKE_PROJECT_NAME}_test src/${CMAKE_PROJECT_NAME}_test.cpp)

add_subdirectory(src)

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
        lib/SFML/include
        lib/googletest/googletest/include
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}_test PRIVATE
    sfml-graphics
    gtest
    gtest_main
)
