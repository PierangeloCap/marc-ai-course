#!/bin/bash


# Set up environmental variables: edit to fit your necessities
CMAKE='cmake' #Note: CMake 3.14.2 required
GENERATOR="CodeBlocks - Unix Makefiles" #Run `${CMAKE} --help` to list generators available on your machine
ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )
JHOME=/usr/lib/jvm/jdk-12.0.1
MARC_ROOT=${ROOT}/marc
JMARC_ROOT=${ROOT}/jmarc
JMARC_NATIVE_ROOT=${JMARC_ROOT}/lib/native
ROOT_BUILD=${ROOT}/build
MARC_BUILD=${ROOT_BUILD}/marc
JMARC_BUILD=${ROOT_BUILD}/jmarc
JMARC_NATIVE_BUILD=${ROOT_BUILD}/jmarc_native

# Create build directories
for dir in ${ROOT_BUILD} ${MARC_BUILD} ${JMARC_BUILD} ${JMARC_NATIVE_BUILD}; do
    if [ ! -d ${dir} ]; then
        mkdir ${dir};
    fi;
done


# Build MARC

cd ${MARC_BUILD}
${CMAKE} -DCMAKE_BUILD_TYPE=Release -G "${GENERATOR}" ${MARC_ROOT}
make

# Build JMARC
# 1. Build Java code

JMARC_SRC=${JMARC_ROOT}/src
JTARGET=$(find ${JMARC_SRC} -wholename *.java)
${JHOME}/bin/javac -h ${JMARC_ROOT}/lib/native/header/jni -d ${JMARC_BUILD} ${JTARGET}

# 2. Build Native lib

cd ${JMARC_NATIVE_BUILD}
${CMAKE} -DCMAKE_BUILD_TYPE=Release -DMARC_BUILD_DIR:STRING=${MARC_BUILD} -DMARC_HOME:STRING=${MARC_ROOT} -G "${GENERATOR}" ${JMARC_NATIVE_ROOT}
make

