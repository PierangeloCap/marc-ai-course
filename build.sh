#!/bin/bash


CMAKE='cmake' #Note: CMake 3.14.2 required
GENERATOR="CodeBlocks - Unix Makefiles" #Run `${CMAKE} --help` to list generators available on your machine
ROOT=$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )
JHOME=/usr/lib/jvm/java-21-openjdk-amd64

export JAVA_HOME="$JHOME"

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

JMARC_SRC=${JMARC_ROOT}/src
JTARGET=$(find ${JMARC_SRC} -wholename *.java)
${JHOME}/bin/javac -h ${JMARC_ROOT}/lib/native/header/jni -d ${JMARC_BUILD} ${JTARGET}


cd ${JMARC_NATIVE_BUILD}
${CMAKE} -DCMAKE_BUILD_TYPE=Release -DMARC_BUILD_DIR:STRING=${MARC_BUILD} -DMARC_HOME:STRING=${MARC_ROOT} -G "${GENERATOR}" ${JMARC_NATIVE_ROOT}
make



# echo "Compilazione del Main in corso..."

# JMARC_EXAMPLE=${JMARC_ROOT}/examples/NQueens

# JMARC_TEST_BUILD=${ROOT_BUILD}/test/jmarc

# if [ ! -d ${JMARC_TEST_BUILD} ]; then
#     mkdir -p ${JMARC_TEST_BUILD};
# fi;

# APP_TARGET=$(find ${JMARC_EXAMPLE} -wholename *.java)

# ${JHOME}/bin/javac -cp ${JMARC_BUILD} -d ${JMARC_TEST_BUILD} ${APP_TARGET}

# echo "Compilazione Main completata."

# ... (tutto il codice precedente per MARC e JMARC rimane uguale) ...

# 3. Compilazione delle Applicazioni (NQueens + ProteinFolding)
echo "Compilazione degli esempi (NQueens, ProteinFolding, ecc)..."

# PUNTO CHIAVE: Invece di puntare a NQueens, puntiamo alla cartella genitore 'examples'
EXAMPLE_SRC_ROOT=${JMARC_ROOT}/examples

# Cartella di output per i file .class compilati
JMARC_TEST_BUILD=${ROOT_BUILD}/test/jmarc

# Creiamo la cartella di destinazione se non esiste
if [ ! -d ${JMARC_TEST_BUILD} ]; then
    mkdir -p ${JMARC_TEST_BUILD};
fi;

# Troviamo TUTTI i file .java dentro la cartella examples (ricorsivamente)
# Questo troverà sia NQueens che ProteinFolding che GeometricTemperature
APP_TARGETS=$(find ${EXAMPLE_SRC_ROOT} -name "*.java")

if [ -z "$APP_TARGETS" ]; then
    echo "ERRORE: Nessun file Java trovato in ${EXAMPLE_SRC_ROOT}"
    exit 1
fi

# Compiliamo tutto insieme
# -cp ${JMARC_BUILD}: Include la libreria JMARC base
# -d ${JMARC_TEST_BUILD}: Mette i .class compilati nella cartella di test
${JHOME}/bin/javac -cp ${JMARC_BUILD} -d ${JMARC_TEST_BUILD} ${APP_TARGETS}

echo "Compilazione Esempi completata."

# --- SUGGERIMENTO PER L'ESECUZIONE ---
# Aggiungo uno script helper per lanciare facilmente ProteinFolding
RUN_SCRIPT=${ROOT}/run_protein.sh
# ... (parte precedente del build.sh) ...

RUN_SCRIPT=${ROOT}/run_protein.sh

# Scrittura del file run_protein.sh riga per riga
echo "#!/bin/bash" > ${RUN_SCRIPT}

# Calcoliamo il percorso assoluto della cartella corrente per evitare errori
echo "ROOT_DIR=\$(pwd)" >> ${RUN_SCRIPT}

# Definiamo dove sono le librerie native
echo "NATIVE_LIB=\"\${ROOT_DIR}/build/jmarc_native\"" >> ${RUN_SCRIPT}

# --- ECCO LA RIGA FONDAMENTALE ---
echo "export LD_LIBRARY_PATH=\"\${NATIVE_LIB}:\${LD_LIBRARY_PATH}\"" >> ${RUN_SCRIPT}

# Comando di avvio Java
echo "\${JAVA_HOME}/bin/java -cp \${ROOT_DIR}/build/jmarc:\${ROOT_DIR}/build/test/jmarc jmarc.examples.proteinfolding.MainProtein" >> ${RUN_SCRIPT}

chmod +x ${RUN_SCRIPT}
echo "Creato script di avvio corretto: ${RUN_SCRIPT}"

chmod +x ${RUN_SCRIPT}
echo "Creato script di avvio: ${RUN_SCRIPT}"
