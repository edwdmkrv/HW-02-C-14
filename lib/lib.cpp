#include "lib.hpp"

#include <stdexcept>
#include <algorithm>

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

ip_str_t split(std::string const &str, char const d) {
	ip_str_t r;

	std::string::size_type start{};

	for (std::string::size_type stop{str.find_first_of(d)};
	     stop != std::string::npos;
	     stop = str.find_first_of(d, start = stop + 1)) {

		r.push_back(str.substr(start, stop - start));
	}

	r.push_back(str.substr(start));

	return r;
}

using namespace std::literals::string_literals;

ip_t::ip_t(ip_str_t const &ip_str) {
	if (ip_str.size() != octets_num) {
		throw std::runtime_error{__PRETTY_FUNCTION__ + ": IP address must have exactly "s + std::to_string(octets_num) + " octets"s};
	}

	unsigned octet_num{ip_t::octets_num};

	for (auto const &item: ip_str) {
		auto const octet{std::stoul(item)};

		if (octet > octet_max_value) {
			throw std::out_of_range{__PRETTY_FUNCTION__ + "IP address octet value cannot exceed "s + std::to_string(octet_max_value)};
		}

		octets |= octet << --octet_num * octet_digits;
	}
}

unsigned ip_t::const_iterator::operator *() const {
	if (n >= ip_t::octet_digits) {
		throw std::out_of_range{__PRETTY_FUNCTION__ + "Invalid iterator value"s};
	}

	return (ip.octets >> n * ip_t::octet_digits) & octet_max_value;
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

std::ostream &operator <<(std::ostream &o, ip_t const &ip) {
	bool dot{};

	for (auto const &octet: ip) {
		o << (dot ? "." : "") << octet;
		dot = true;
	}

	return o;
}

void issue(std::ostream &o, ip_pool_t const &ip_pool, filter_t const &filter) {
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
