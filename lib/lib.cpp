#include "lib.hpp"

#include <stdexcept>
#include <algorithm>
#include <iostream>

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

ip_t::ip_t(ip_str_t const &ip_str): octets{} {
	if (ip_str.size() != octets_num) {
		throw std::runtime_error{__PRETTY_FUNCTION__ + ": IP address must have exactly "s + std::to_string(octets_num) + " octets"s};
	}

	for (auto const &item: ip_str) {
		auto const octet{std::stoul(item)};

		if (octet > octet_max_value) {
			throw std::out_of_range{__PRETTY_FUNCTION__ + "IP address octet value cannot exceed "s + std::to_string(octet_max_value)};
		}

		octets = (octets << octet_digits) | octet;
	}
}

unsigned ip_t::const_iterator::operator *() const {
	if (n >= ip_t::octet_digits) {
		throw std::out_of_range{__PRETTY_FUNCTION__ + "Invalid iterator value"s};
	}

	return (ip.octets >> (ip_t::octets_num - n - 1) * ip_t::octet_digits) & octet_max_value;
}

ip_pool_t parse(std::istream &i) {
	ip_pool_t ip_pool;

	for(std::string line; std::getline(i, line);) {
		ip_pool.push_back(split(split(line, '\t').at(0), '.'));
	}

	return ip_pool;
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
			o << ip << std::endl;
		}
	}
}
