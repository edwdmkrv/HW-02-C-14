cmake_minimum_required (VERSION 3.12)

# Project stuff
project (ipfilter_lib
	VERSION 0.0.${TRAVIS_BUILD_NUMBER}
	DESCRIPTION "Homework 2 IP filter implementation library"
	HOMEPAGE_URL "https://github.com/edwdmkrv/HW-02-C-14/tree/master/lib"
	LANGUAGES CXX
)

# Library stuff
add_library (lib SHARED lib.cpp)

set_target_properties (lib PROPERTIES
	CXX_STANDARD 14
	CXX_EXTENSIONS OFF
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-pedantic;-Wall;-Wextra"
	INCLUDE_DIRECTORIES "${CMAKE_BINARY_DIR};${CMAKE_SOURCE_DIR}/lib"
)

# Automatically added to the compile options for the targets linked against the library
set_property (TARGET lib APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
	"${CMAKE_BINARY_DIR}"
	"${CMAKE_SOURCE_DIR}/lib"
)

install (TARGETS lib LIBRARY DESTINATION Debug/lib CONFIGURATIONS Debug COMPONENT lib)
install (TARGETS lib LIBRARY DESTINATION lib CONFIGURATIONS Release COMPONENT lib)
