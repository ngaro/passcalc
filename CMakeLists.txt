cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(PassCalc VERSION 0.1 LANGUAGES CXX)

set(PROGNAME passcalc)
set(SRCDIR cmdline)

#if(DEFINED ENV{COMPILER})
#	set(CMAKE_C++_COMPILER $ENV{COMPILER})
#else()
#	find_program(COMPILER_TO_USE g++)
#	if(COMPILER_TO_USE)
#		set(CMAKE_CXX_COMPILER ${COMPILER_TO_USE})
#	endif()
#endif()

set(CMAKE_CXX_FLAGS "-O0 -ggdb -Wall -Wextra -pedantic")

aux_source_directory(${SRCDIR} SOURCECODE)
add_executable(${PROGNAME} ${SOURCECODE})
target_link_libraries(${PROGNAME} ssl crypto)
