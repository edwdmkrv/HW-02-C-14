cmake_minimum_required (VERSION 3.6)

# Project stuff
project (ipfilter_src
	VERSION 0.0.${TRAVIS_BUILD_NUMBER}
	DESCRIPTION "Homework 2 IP filter implementation itself"
	HOMEPAGE_URL "https://github.com/edwdmkrv/HW-02-C-14/tree/master/src"
	LANGUAGES CXX
)

# Program stuff
add_executable (ipfilter ipfilter.cpp)

set_target_properties (ipfilter PROPERTIES
	CXX_STANDARD 14
	CXX_EXTENSIONS OFF
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-pedantic;-Wall;-Wextra"
	LINK_LIBRARIES "lib;${CMAKE_THREAD_LIBS_INIT}"
	BUILD_RPATH "${CMAKE_BINARY_DIR}/${LIB_SUBDIR}/lib"
	INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_SUBDIR}/lib"
)

install (TARGETS ipfilter RUNTIME DESTINATION Debug/bin CONFIGURATIONS Debug COMPONENT prog)
install (TARGETS ipfilter RUNTIME DESTINATION bin CONFIGURATIONS Release COMPONENT prog)
