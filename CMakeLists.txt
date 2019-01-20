cmake_minimum_required (VERSION 3.6)

# Version/options stuff
set (TRAVIS_BUILD_NUMBER "$ENV{TRAVIS_BUILD_NUMBER}")

if ("${TRAVIS_BUILD_NUMBER}" STREQUAL "")
	set (TRAVIS_BUILD_NUMBER "1")
endif ("${TRAVIS_BUILD_NUMBER}" STREQUAL "")

option (BUILD_TYPE_RELEASE "Is build type Release")

if (BUILD_TYPE_RELEASE)
	set (CMAKE_BUILD_TYPE "Release")
	set (LIB_SUBDIR ".")
else (BUILD_TYPE_RELEASE)
	set (CMAKE_BUILD_TYPE "Debug")
	set (LIB_SUBDIR "Debug")
endif (BUILD_TYPE_RELEASE)

# Project stuff
project (ipfilter
	VERSION 0.0.${TRAVIS_BUILD_NUMBER}
	DESCRIPTION "Homework 2 IP filter implementation"
	HOMEPAGE_URL "https://github.com/edwdmkrv/HW-02-C-14"
	LANGUAGES CXX
)

find_package (GTest REQUIRED)
find_package (Threads REQUIRED)

configure_file (version.hpp.in version.hpp)

# Library stuff
add_subdirectory (lib)

add_executable (ipfilter ipfilter.cpp)

set_target_properties (ipfilter PROPERTIES
	CXX_STANDARD 14
	CXX_EXTENSIONS OFF
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-pedantic;-Wall;-Wextra"
)

set_target_properties (ipfilter PROPERTIES
	BUILD_RPATH "${CMAKE_BINARY_DIR}/${LIB_SUBDIR}/lib"
)

set_target_properties (ipfilter PROPERTIES
	LINK_LIBRARIES "lib;${CMAKE_THREAD_LIBS_INIT}"
	INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_SUBDIR}/lib"
)

install (TARGETS ipfilter RUNTIME DESTINATION Debug/bin CONFIGURATIONS Debug COMPONENT prog)
install (TARGETS ipfilter RUNTIME DESTINATION bin CONFIGURATIONS Release COMPONENT prog)

set (CMAKE_VERBOSE_MAKEFILE OFF)

# CTest stuff
add_subdirectory (tst)
include (CTest)

# CPack stuff
add_subdirectory (pkg)
