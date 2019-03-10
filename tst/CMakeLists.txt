cmake_minimum_required (VERSION 3.6)

# Project stuff
project (ipfilter_tst
	VERSION 0.0.${TRAVIS_BUILD_NUMBER}
	DESCRIPTION "Homework 2 IP filter implementation tests"
	HOMEPAGE_URL "https://github.com/edwdmkrv/HW-02-C-14/tree/master/tst"
	LANGUAGES CXX
)

# Test stuff
add_executable (test_split test_split.cpp)
add_executable (test_parse test_parse.cpp)
add_executable (test_issue test_issue.cpp)

# set_target_properties (test_split test_parse test_issue PROPERTIES
set_target_properties (test_split test_parse test_issue PROPERTIES
	CXX_STANDARD 14
	CXX_EXTENSIONS OFF
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-pedantic;-Wall;-Wextra"
	LINK_LIBRARIES "${GTEST_LIBRARY};${GTEST_MAIN_LIBRARY};lib;${CMAKE_THREAD_LIBS_INIT}"
	BUILD_RPATH "${CMAKE_BINARY_DIR}/${LIB_SUBDIR}/lib"
)

add_test (NAME Test-function-split
	COMMAND test_split
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

add_test (NAME Test-function-parse
	COMMAND test_parse
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

add_test (NAME Test-function-issue
	COMMAND test_issue
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

include (CTest)
