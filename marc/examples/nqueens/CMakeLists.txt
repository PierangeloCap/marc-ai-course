cmake_minimum_required(VERSION 3.14)
project(MARCNQueens_)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(MARCNQueens 
        src/Main.cpp
        src/ExponentialTemperature.cpp
        src/GeometricTemperature.cpp
        src/InvLogTemperature.cpp
        src/MoveQueen.cpp
        src/NQueens.cpp
        src/QueensBoard.cpp
        header/ExponentialTemperature.h
        header/GeometricTemperature.h
        header/InvLogTemperature.h
        header/MoveQueen.h
        header/NQueens.h
        header/QueensBoard.h
        )

include(FindPkgConfig)
find_package(MARC REQUIRED)
target_include_directories(MARCNQueens PUBLIC ${MARC_INCLUDE})
target_link_libraries(MARCNQueens ${MARC_LIBRARY_PATH})