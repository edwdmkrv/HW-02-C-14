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

ip_pool_t parse(std::istream &i) {
	ip_pool_t ip_pool;

	for(std::string line; std::getline(i, line);) {
		ip_pool.push_back(split(split(line, '\t').at(0), '.'));
	}

	return ip_pool;
}

void sort(ip_pool_t &ip_pool) {
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
}

void issue(std::ostream &o, ip_pool_t const &ip_pool, filter_t const &filter = [](ip_t const &) {return true;}) {
	for (auto const &ip: ip_pool) {
		if (filter(ip)) {
			bool dot{};

			for (auto const &ip_part: ip) {
				o << (dot ? "." : "") << ip_part;
				dot = true;
			}

			o << std::endl;
		}
	}
}

int main() try {
	std::cin.exceptions(std::ostream::badbit);

	ip_pool_t ip_pool{parse(std::cin)};

	sort(ip_pool);

	std::cout.exceptions(std::ostream::badbit | std::ostream::failbit | std::ostream::eofbit);

	for (auto const &filter: std::initializer_list<filter_t>{
			[](ip_t const &) {
				return true;
			},
			[](ip_t const &ip) {
				return ip.at(0) == "1";
			},
			[](ip_t const &ip) {
				return ip.at(0) == "46" &&
				       ip.at(1) == "70";
			},
			[](ip_t const &ip) {
				return ip.at(0) == "46" ||
				       ip.at(1) == "46" ||
				       ip.at(2) == "46" ||
				       ip.at(3) == "46";
			},
			}) {

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
