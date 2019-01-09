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
project (ipfilter VERSION 0.0.${TRAVIS_BUILD_NUMBER})

find_package (GTest REQUIRED)
find_package (Threads REQUIRED)

configure_file (version.hpp.in version.hpp)

add_library (lib SHARED lib.cpp)

add_executable (ipfilter ipfilter.cpp)

add_executable (test_split test_split.cpp)
add_executable (test2 test2.cpp)

set_target_properties (lib ipfilter test_split test2 PROPERTIES
	CXX_STANDARD 14
	CXX_EXTENSIONS OFF
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-pedantic;-Wall;-Wextra"
)

target_include_directories (lib
	PRIVATE "${CMAKE_BINARY_DIR}"
)

set_target_properties (ipfilter test_split test2 PROPERTIES
	BUILD_RPATH "${CMAKE_BINARY_DIR}/${LIB_SUBDIR}/lib"
)

target_link_libraries (ipfilter
	PRIVATE lib
	PRIVATE "${GTEST_LIBRARY}"
	PRIVATE "${GTEST_MAIN_LIBRARY}"
	PRIVATE "${CMAKE_THREAD_LIBS_INIT}"
)

target_link_libraries (test_split
	PRIVATE lib
	PRIVATE "${GTEST_LIBRARY}"
	PRIVATE "${GTEST_MAIN_LIBRARY}"
	PRIVATE "${CMAKE_THREAD_LIBS_INIT}"
)

target_link_libraries (test2
	PRIVATE lib
	PRIVATE "${GTEST_LIBRARY}"
	PRIVATE "${GTEST_MAIN_LIBRARY}"
	PRIVATE "${CMAKE_THREAD_LIBS_INIT}"
)

set_target_properties (ipfilter PROPERTIES
	INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_SUBDIR}/lib"
)

install (TARGETS lib LIBRARY DESTINATION Debug/lib CONFIGURATIONS Debug COMPONENT lib)
install (TARGETS ipfilter RUNTIME DESTINATION Debug/bin CONFIGURATIONS Debug COMPONENT prog)

install (TARGETS lib LIBRARY DESTINATION lib CONFIGURATIONS Release COMPONENT lib)
install (TARGETS ipfilter RUNTIME DESTINATION bin CONFIGURATIONS Release COMPONENT prog)

set (CMAKE_VERBOSE_MAKEFILE OFF)

# CTest stuff
add_test (NAME Test-function-split
	COMMAND test_split
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

add_test (NAME Test-2
	COMMAND test2
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

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
