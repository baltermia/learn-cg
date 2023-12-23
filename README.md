# Learn CG M1

This is a temporary branch, testing out to see if I can configure this shit on my M1 MacBook also. 
Probably switch to some building too like CMake or Premake, time will tell.

This only serves as a note if I decide to leave this project for a few weeks again and return with no idea what the hell I was doing lol

## Installation

Make sure to clone this branch with it's submodules:
```
git clone --recurse-submodules -b m1 https://github.com/baltermia/learn-cg ./learn-cg-m1
```

Required Dependencies:
- glfw3
- cmake
- g++

Make sure you have the MacOS devtools installed:
```
xcode-select --install
```

Install dependencies with brew:
```
brew install cmake
```

## Build Steps

### Building Dependencies

Execute the build script for angle:
```
sh vendor/angle/build/install-build-deps.sh
```

### Building Program

First, build the cmake configuration into the build directory:
```
cmake -B build -S .
```

Then, build the binaries:
```
cmake --build build
```
