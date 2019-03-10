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

	for (auto stop{str.find_first_of(d)};
	     stop != std::string::npos;
	     stop = str.find_first_of(d, start = stop + 1)) {

		r.push_back(str.substr(start, stop - start));
	}

	r.push_back(str.substr(start));

	return r;
}

using namespace std::literals::string_literals;

std::uint8_t ip_t::convert(std::string const &ip_str) {
	auto const octet{std::stoul(ip_str)};

	if (octet > std::numeric_limits<uint8_t>::max()) {
		throw std::runtime_error{__PRETTY_FUNCTION__ + ": IP address octet maximal value is "s + std::to_string(std::numeric_limits<uint8_t>::max())};
	}

	return octet;
}

std::array<std::uint8_t, ip_addr_octets> ip_t::convert(ip_str_t const &ip_str) {
	if (ip_str.size() != ip_addr_octets) {
		throw std::runtime_error{__PRETTY_FUNCTION__ + ": IP address must have exactly "s + std::to_string(ip_addr_octets) + " octets"s};
	}

	return {convert(ip_str.at(0)), convert(ip_str.at(1)), convert(ip_str.at(2)), convert(ip_str.at(3))};
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
		o << (dot ? "." : "") << static_cast<unsigned>(octet);
		dot = true;
	}

	return o;
}

std::ostream &operator <<(std::ostream &o, ip_pool_filtered_proxy_t const &proxy) {
	for (auto const &ip: proxy.ip_pool) {
		if (proxy.filter(ip)) {
			o << ip << std::endl;
		}
	}

	return o;
}
