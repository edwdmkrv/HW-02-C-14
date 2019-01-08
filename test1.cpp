#include "lib.hpp"

#include <cstdlib>
#include <iostream>

int main() {
	return ver() == std::to_string(major()) + '.' + std::to_string(minor()) + '.' + std::to_string(patch()) ? EXIT_SUCCESS : EXIT_FAILURE;
}
