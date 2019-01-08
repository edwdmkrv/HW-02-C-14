#include "lib.hpp"

#include <version.hpp>

std::string ver() {
	return PROJECT_VERSION;
}

unsigned major() {
	return PROJECT_VERSION_MAJOR;
}

unsigned minor() {
	return PROJECT_VERSION_MINOR;
}

unsigned patch() {
	return PROJECT_VERSION_PATCH;
}

std::string msg() {
	return "Yes!";
}
