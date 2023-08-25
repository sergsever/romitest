cmake_minimum_required(VERSION 3.25)
project(romitest)
add_compile_options(
-Wall
)
set (SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/ComReader.cpp
 	${CMAKE_CURRENT_SOURCE_DIR}/Message.cpp
)
set (HEADERS
${CMAKE_CURRENT_SOURCE_DIR}/ComReader.h
${CMAKE_CURRENT_SOURCE_DIR}/Cessage.h
)
add_executable(comreader ${SOURCES} )
