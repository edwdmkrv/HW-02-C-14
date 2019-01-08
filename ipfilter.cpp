#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#include <unistd.h>

using ip_t = std::vector<std::string>;
using ip_pool_t = std::vector<ip_t>;
using filter_t = std::function<bool(ip_t const &)>;

ip_t split(std::string const &str, char const d) {
	ip_t r;

	std::string::size_type start{};

	for (std::string::size_type stop{str.find_first_of(d)};
	     stop != std::string::npos;
	     stop = str.find_first_of(d, start = stop + 1)) {

		r.push_back(str.substr(start, stop - start));
	}

	r.push_back(str.substr(start));

	return r;
}

void issue(ip_pool_t const &ip_pool, filter_t const &filter = [](ip_t const &) {return true;}) {
	for (auto const &ip: ip_pool) {
		if (filter(ip)) {
			bool dot{};

			for (auto const &ip_part: ip) {
				std::cout << (dot ? "." : "") << ip_part;
				dot = true;
			}

			std::cout << std::endl;
		}
	}
}

int main() try {
	ip_pool_t ip_pool;

	std::cin.exceptions(std::ostream::badbit);

	for(std::string line; std::getline(std::cin, line);) {
		ip_pool.push_back(split(split(line, '\t').at(0), '.'));
	}

        // TODO reverse lexicographically sort
	std::sort(std::begin(ip_pool), std::end(ip_pool),
		  [](auto const &l, auto const &r) {
		  	for (auto l_it{std::cbegin(l)}, l_end{std::cend(l)}, r_it{std::cbegin(r)}, r_end{std::cend(r)};
			     l_it != l_end && r_it != r_end;
			     ++l_it, ++r_it) {

				auto const &lv{std::stoi(*l_it)}, &rv{std::stoi(*r_it)};

				if (lv > rv) {
					return true;
				}

				if (lv < rv) {
					return false;
				}
			}

		  	return false;
		  }
	);

	std::cout.exceptions(std::ostream::badbit | std::ostream::failbit | std::ostream::eofbit);

	issue(ip_pool);

	issue(ip_pool, [](ip_t const &ip) {
	      return ip.at(0) == "1";
	});

	issue(ip_pool, [](ip_t const &ip) {
	      return ip.at(0) == "46" &&
	             ip.at(1) == "70";
	});

	issue(ip_pool, [](ip_t const &ip) {
	      return ip.at(0) == "46" ||
	             ip.at(1) == "46" ||
	             ip.at(2) == "46" ||
	             ip.at(3) == "46";
	});

	return EXIT_SUCCESS;
} catch (std::exception const &e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return EXIT_FAILURE;
} catch (...) {
	std::cerr << "Error: " << "unidentified exception" << std::endl;
	return EXIT_FAILURE;
}
