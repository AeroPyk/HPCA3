cmake_minimum_required(VERSION 3.16)
project(A3 C)

set(CMAKE_C_FLAGS -fopenmp)
set(CMAKE_C_STANDARD 99)

find_package(MPI REQUIRED) # define MPI function

add_executable(main main.c)
add_executable(Ex1 Exercise1.c)

target_link_libraries(main ${MPI_LIBRARIES})
target_link_libraries(Ex1 ${MPI_LIBRARIES})


# Include MPI includes # Not necessary since I copied them into the MinGW include folder
#include_directories(${MPI_INCLUDE_PATH})
#if(MPI_COMPILE_FLAGS)
#    set_target_properties(mainExec PROPERTIES
#            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
#endif()
#if(MPI_LINK_FLAGS)
#    set_target_properties(mainExec PROPERTIES
#            LINK_FLAGS "${MPI_LINK_FLAGS}")
#endif()