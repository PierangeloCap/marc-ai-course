#!/bin/bash


# Set up environmental variables: edit to fit your necessities
CMAKE='cmake' #Note: CMake 3.14.2 required
GENERATOR="CodeBlocks - Unix Makefiles" #Run `${CMAKE} --help` to list generators available on your machine
ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )
JHOME=/usr/lib/jvm/java-21-openjdk-amd64

export JAVA_HOME="$JHOME"

# Aggiunge i percorsi degli header Java direttamente per sicurezza
export CPLUS_INCLUDE_PATH="$JHOME/include:$JHOME/include/linux:$CPLUS_INCLUDE_PATH"

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


# ... (dopo l'ultimo make)

# 3. Compilazione del Main (Applicazione)
echo "Compilazione del Main in corso..."

# Definiamo le cartelle (prendendo spunto dal primo script)
JMARC_EXAMPLE=${JMARC_ROOT}/examples/NQueens
# OPPURE, se il tuo Main personalizzato è altrove, metti il percorso giusto qui:
# JMARC_EXAMPLE=${JMARC_ROOT}/src 

JMARC_TEST_BUILD=${ROOT_BUILD}/test/jmarc

# Creiamo la cartella di destinazione se non esiste
if [ ! -d ${JMARC_TEST_BUILD} ]; then
    mkdir -p ${JMARC_TEST_BUILD};
fi;

# Troviamo i file java del Main/Esempio
APP_TARGET=$(find ${JMARC_EXAMPLE} -wholename *.java)

# Compiliamo il Main mettendo nel classpath la libreria appena costruita (JMARC_BUILD)
# e salvando il risultato in JMARC_TEST_BUILD
${JHOME}/bin/javac -cp ${JMARC_BUILD} -d ${JMARC_TEST_BUILD} ${APP_TARGET}

echo "Compilazione Main completata."
