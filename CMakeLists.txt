cmake_minimum_required(VERSION 3.26)

# link vcpkg libs
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# project settings
set(CMAKE_CXX_STANDARD 23)

# project info
project(learn_cg_m1)

# include directories and source files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# executable
add_executable(learn_cg_m1 ${SOURCES})

# dependencies
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(learn_cg_m1 PRIVATE glfw)
