#include "lib.hpp"

#include <cstdlib>
#include <iostream>

int main() {
	return std::cout << "Version: " << ver() << std::endl ? EXIT_SUCCESS : EXIT_FAILURE;
}
