cmake_minimum_required (VERSION 3.6)

# Project stuff
project (ipfilter_pkg
	VERSION 0.0.${TRAVIS_BUILD_NUMBER}
	DESCRIPTION "Homework 2 IP filter implementation"
	HOMEPAGE_URL "https://github.com/edwdmkrv/HW-02-C-14/tree/master/pkg"
	LANGUAGES CXX
)

# CPack stuff
set (CPACK_GENERATOR DEB)

set (CPACK_COMPONENT_PROG_DESCRIPTION
"program
The sample IP filter program depending on the corresponding library.")

set (CPACK_COMPONENT_LIB_DESCRIPTION
"library
The IP filter library the corresponding program depends on.")

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
