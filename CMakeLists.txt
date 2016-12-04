cmake_minimum_required(VERSION 2.8)
project(amf)

set (CMAKE_CXX_STANDARD 11)

find_library(FFTW_LIBRARY NAMES fftw3)

file(GLOB CPPFILES "source/*.cpp" "source/*.h" )
add_executable(amf ${CPPFILES})

target_link_libraries(amf sfml-graphics sfml-window sfml-system sfml-audio ${FFTW_LIBRARY})
