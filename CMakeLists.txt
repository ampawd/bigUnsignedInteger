cmake_minimum_required (VERSION 3.1.0)


# enable c++11 support
set (CMAKE_CXX_STANDARD 11)


# project name
project (bigUnsignedInt)


# includes
include_directories (${CMAKE_SOURCE_DIR}/include)


set(HEADER_FILES ${CMAKE_SOURCE_DIR}/include/big_uint.h)


# sources
file(GLOB SOURCES src/*.cpp)


# executable
add_executable (biguint 
	${SOURCES} main.cpp 
	${HEADER_FILES}
)