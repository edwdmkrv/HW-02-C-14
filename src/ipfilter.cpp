#include <cstdlib>
#include <algorithm>
#include <iostream>

#include "lib.hpp"

int main() try {
	std::cin.exceptions(std::ostream::badbit);

	ip_pool_t ip_pool{parse(std::cin)};

	std::sort(std::begin(ip_pool), std::end(ip_pool), std::greater<ip_t>{});

	std::cout.exceptions(std::ostream::badbit | std::ostream::failbit | std::ostream::eofbit);

	for (
		auto const &filter:
		std::initializer_list<filter_t>{
			[](ip_t const &) {
				return true;
			},
			[](ip_t const &ip) {
				return ip.at(0) == 1;
			},
			[](ip_t const &ip) {
				return ip.at(0) == 46 &&
				       ip.at(1) == 70;
			},
			[](ip_t const &ip) {
				auto it{std::cbegin(ip)};

				return ip.at(0) == 46 ||
				       ip.at(1) == 46 ||
				       ip.at(2) == 46 ||
				       ip.at(3) == 46;
			}
		}
	) {
		issue(std::cout, ip_pool, filter);
	}

	return EXIT_SUCCESS;
} catch (std::exception const &e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return EXIT_FAILURE;
} catch (...) {
	std::cerr << "Error: " << "unidentified exception" << std::endl;
	return EXIT_FAILURE;
}
