#!/bin/bash
ROOT_DIR=$(pwd)
NATIVE_LIB="${ROOT_DIR}/build/jmarc_native"
export LD_LIBRARY_PATH="${NATIVE_LIB}:${LD_LIBRARY_PATH}"
${JAVA_HOME}/bin/java -cp ${ROOT_DIR}/build/jmarc:${ROOT_DIR}/build/test/jmarc jmarc.examples.proteinfolding.MainProtein
