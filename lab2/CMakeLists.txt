cmake_minimum_required(VERSION 3.10)
project(HeatTransferModel)

set(CMAKE_CXX_STANDARD 17)

add_library(Solver SHARED solver.cpp)
add_executable(HeatTransfer main.cpp utils.cpp)

target_link_libraries(HeatTransfer Solver)
