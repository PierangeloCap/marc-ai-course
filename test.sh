#!/bin/bash


# Set up environmental variables: edit to fit your necessities
CMAKE='cmake' #Note: CMake 3.14.2 required
GENERATOR="CodeBlocks - Unix Makefiles" #Run `${CMAKE} --help` to list generators available on your machine
ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )
JHOME=/usr/lib/jvm/jdk-12.0.1
MARC_ROOT=${ROOT}/marc
MARC_EXAMPLE=${MARC_ROOT}/examples/nqueens
JMARC_ROOT=${ROOT}/jmarc
JMARC_EXAMPLE=${JMARC_ROOT}/examples/NQueens

ROOT_BUILD=${ROOT}/build
MARC_BUILD=${ROOT_BUILD}/marc
JMARC_BUILD=${ROOT_BUILD}/jmarc
JMARC_NATIVE_BUILD=${ROOT_BUILD}/jmarc_native

ROOT_TEST=${ROOT_BUILD}/test
MARC_TEST=${ROOT_TEST}/marc
JMARC_TEST=${ROOT_TEST}/jmarc


# Create build directories
for dir in ${ROOT_TEST} ${MARC_TEST} ${JMARC_TEST}; do
    if [ ! -d ${dir} ]; then
        mkdir ${dir};
    fi;
done


# Test MARC
echo "Testing MARC..."
cd ${MARC_TEST}
${CMAKE} -DCMAKE_BUILD_TYPE=Release -DMARC_BUILD_DIR:STRING=${MARC_BUILD} -DMARC_HOME:STRING=${MARC_ROOT} -G "${GENERATOR}" ${MARC_EXAMPLE}
make
./MARCNQueens > /dev/null
[ $? -eq 0 ] && echo "MARC test successful!" || echo "MARC test failed."


# Test JMARC
echo "Testing JMARC..."
JTARGET=$(find ${JMARC_EXAMPLE} -wholename *.java)
${JHOME}/bin/javac -cp ${JMARC_BUILD} -d ${JMARC_TEST} ${JTARGET}
cd ${JMARC_TEST}
${JHOME}/bin/java -Djava.library.path=${JMARC_NATIVE_BUILD} -classpath ":${JMARC_TEST}:${JMARC_BUILD}" Main > /dev/null
[ $? -eq 0 ] && echo "JMARC test successful!" || echo "JMARC test failed."
