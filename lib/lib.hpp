#ifndef __LIB_INCLUDED
#define __LIB_INCLUDED

#include <cstdint>
#include <limits>
#include <string>
#include <array>
#include <vector>
#include <functional>
#include <iostream>

std::string ver();

unsigned major();
unsigned minor();
unsigned patch();

using ip_str_t = std::vector<std::string>;

enum: unsigned {ip_addr_octets = 4};

class ip_t: public std::array<std::uint8_t, ip_addr_octets> {
private:
	static std::uint8_t convert(std::string const &ip_str);
	static std::array<std::uint8_t, ip_addr_octets> convert(ip_str_t const &ip_str);

public:
	ip_t(ip_str_t const &ip_str): std::array<std::uint8_t, ip_addr_octets>{convert(ip_str)} {
	}
};

using ip_pool_t = std::vector<ip_t>;
using filter_t = std::function<bool(ip_t const &)>;

class ip_pool_filtered_proxy_t { // Non-owning proxy
private:
	ip_pool_t const &ip_pool;
	filter_t const &filter;

public:
	ip_pool_filtered_proxy_t(ip_pool_t const &ip_pool, filter_t const &filter) noexcept:
	ip_pool{ip_pool}, filter{filter} {
	}

	friend std::ostream &operator <<(std::ostream &o, ip_pool_filtered_proxy_t const &proxy);
};

ip_str_t split(std::string const &str, char const d);
ip_pool_t parse(std::istream &i);

std::ostream &operator <<(std::ostream &o, ip_t const &ip);

#endif
