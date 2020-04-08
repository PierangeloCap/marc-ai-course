cmake_minimum_required(VERSION 3.14)
project(JMARC)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_library(JMARCNative SHARED
    src/backend/JNIWrap.cpp
    src/backend/JDimensionType.cpp
    src/backend/JState.cpp
    src/backend/JAction.cpp
    src/backend/JProblem.cpp
    src/backend/JSolution.cpp
    src/backend/JInitStateProblem.cpp
    src/backend/JTemperature.cpp
    src/backend/JStateInternal.cpp
    header/backend/JState.h
    header/backend/JTemperature.h
    header/backend/JDimensionType.h
    header/backend/JSolution.h
    header/backend/JAction.h
    header/backend/JProblem.h
    header/backend/JNIWrap.h
    header/backend/JInitStateProblem.h
    header/backend/JStateInternal.h
    src/jni/jmarc_MARCNativeWrapper.cpp
    src/jni/jmarc_modeling_MARCAction.cpp
    src/jni/jmarc_modeling_MARCInitStateProblem.cpp
    src/jni/jmarc_modeling_MARCProblem.cpp
    src/jni/jmarc_modeling_MARCSolution.cpp
    src/jni/jmarc_modeling_MARCState.cpp
    src/jni/jmarc_solving_MARCFirstChoiceHillClimbing.cpp
    src/jni/jmarc_solving_MARCSteepestDescent.cpp
    src/jni/jmarc_solving_MARCSequentialSolver.cpp
    src/jni/jmarc_solving_MARCSimulatedAnnealing.cpp
    src/jni/jmarc_solving_MARCSolver.cpp
    src/jni/jmarc_solving_MARCORBSolver.cpp
    src/jni/jmarc_solving_MARCSolverMonitor.cpp
    src/jni/jmarc_solving_MARCTemperature.cpp
    header/jni/jmarc_MARCNativeWrapper.h
    header/jni/jmarc_solving_MARCSolver.h
    header/jni/jmarc_solving_MARCTemperature.h
    header/jni/jmarc_modeling_MARCState.h
    header/jni/jmarc_solving_MARCSimulatedAnnealing.h
    header/jni/jmarc_solving_MARCORBSolver.h
    header/jni/jmarc_solving_MARCSolverMonitor.h
    header/jni/jmarc_modeling_MARCAction.h
    header/jni/jmarc_modeling_MARCInitStateProblem.h
    header/jni/jmarc_modeling_MARCProblem.h
    header/jni/jmarc_solving_MARCSequentialSolver.h
    header/jni/Handle.h
    header/jni/jmarc_modeling_MARCSolution.h
    header/jni/jmarc_solving_MARCFirstChoiceHillClimbing.h
    header/jni/jmarc_solving_MARCSteepestDescent.h
)

set_property(TARGET JMARCNative PROPERTY POSITION_INDEPENDENT_CODE ON)

include(FindPkgConfig)
find_package(MARC REQUIRED)
target_include_directories(JMARCNative PUBLIC ${MARC_INCLUDE})
target_link_libraries(JMARCNative PUBLIC ${MARC_LIBRARY_PATH})

find_package(JNI REQUIRED)
target_include_directories(JMARCNative PUBLIC ${JNI})

#####################

