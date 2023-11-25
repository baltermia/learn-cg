cmake_minimum_required(VERSION 3.26)

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
add_subdirectory(vendor/glfw)
target_link_libraries(learn_cg_m1 PRIVATE glfw)
