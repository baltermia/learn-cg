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

# Dependencies:

# GLFW ------------------------------------------------------------------------

add_subdirectory(vendor/glfw)

# ANGLE -----------------------------------------------------------------------

# Define path to ANGLE libraries
set(ANGLE_LIBRARY_DIR vendor/angle/out/Release)

# Find ANGLE libraries
find_library(ANGLE_GLESv2_LIBRARY libGLESv2.dylib PATHS ${ANGLE_LIBRARY_DIR})
find_library(ANGLE_EGL_LIBRARY libEGL.dylib PATHS ${ANGLE_LIBRARY_DIR})

# Add ANGLE include directory
target_include_directories(${PROJECT_NAME} PRIVATE vendor/angle/include)

# -----------------------------------------------------------------------------

# Finally link all libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${ANGLE_EGL_LIBRARY} ${ANGLE_GLESv2_LIBRARY})
