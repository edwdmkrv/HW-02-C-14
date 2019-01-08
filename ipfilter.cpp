#include "lib.hpp"

#include <cstdlib>

#include <iostream>

int main(int argc, char *argv[]) {
	std::cout << "Version: " << ver() << std::endl;
	std::cout << "Message: " << msg() << std::endl;
	return EXIT_SUCCESS;
}
