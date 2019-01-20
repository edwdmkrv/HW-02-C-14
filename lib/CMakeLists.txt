cmake_minimum_required (VERSION 3.6)

# Project stuff
project (ipfilter
	VERSION 0.0.${TRAVIS_BUILD_NUMBER}
	DESCRIPTION "Homework 2 IP filter implementation library"
	HOMEPAGE_URL "https://github.com/edwdmkrv/HW-02-C-14/tree/master/lib"
	LANGUAGES CXX
)

add_library (lib SHARED lib.cpp)

set_target_properties (lib PROPERTIES
	CXX_STANDARD 14
	CXX_EXTENSIONS OFF
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-pedantic;-Wall;-Wextra"
	INCLUDE_DIRECTORIES "${CMAKE_BINARY_DIR};${CMAKE_SOURCE_DIR}/lib"
)

install (TARGETS lib LIBRARY DESTINATION Debug/lib CONFIGURATIONS Debug COMPONENT lib)
install (TARGETS lib LIBRARY DESTINATION lib CONFIGURATIONS Release COMPONENT lib)
