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

add_subdirectory (lib)

add_executable (ipfilter ipfilter.cpp)

set_target_properties (ipfilter PROPERTIES
	CXX_STANDARD 14
	CXX_EXTENSIONS OFF
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-pedantic;-Wall;-Wextra"
)

set_target_properties (ipfilter PROPERTIES
	INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/lib"
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
set (CPACK_GENERATOR DEB)

set (CPACK_COMPONENT_PROG_DESCRIPTION
"program
 The sample program depending on the sample library.")

set (CPACK_COMPONENT_LIB_DESCRIPTION
"library
 The sample library the smaple program depends on.")

set (CPACK_DEB_COMPONENT_INSTALL ON)
set (CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
set (CPACK_DEBIAN_PROG_PACKAGE_DEPENDS ipfilter-lib)
set (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

set (CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set (CPACK_PACKAGE_ARCHITECTURE "amd64")
set (CPACK_PACKAGE_CONTACT myname@company.com)
set (CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

include (CPack)
