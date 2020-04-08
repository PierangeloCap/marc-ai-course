#!/usr/bin/bash

#Note: CMake 3.14.2 required
CMAKE='cmake'
#Run `${CMAKE} --help` to list generators available on your machine
GENERATOR="CodeBlocks - Unix Makefiles"

mkdir build
cd build
${CMAKE} -DCMAKE_BUILD_TYPE=Release -G "${GENERATOR}" ..
make
