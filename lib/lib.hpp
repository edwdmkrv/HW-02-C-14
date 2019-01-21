#ifndef __LIB_INCLUDED
#define __LIB_INCLUDED

#include <cstdint>
#include <limits>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

std::string ver();

unsigned major();
unsigned minor();
unsigned patch();

using ip_str_t = std::vector<std::string>;

class ip_t {
public:
	using ip_base_type = std::uint32_t;
	using octet_base_type = std::uint8_t;

	enum: ip_base_type {
		octets_num = sizeof(ip_base_type) / sizeof(octet_base_type),
		octet_max_value = std::numeric_limits<octet_base_type>::max(),
		octet_digits = std::numeric_limits<octet_base_type>::digits
	};

private:
	ip_base_type octets;

public:
	ip_t(ip_str_t const &ip_str);

	class const_iterator {
	private:
		ip_t const &ip;
		unsigned n;

	public:
		const_iterator(ip_t const &ip, unsigned const n): ip{ip}, n{n} {
		}

		bool operator !=(const_iterator const &it) const noexcept {
			return n != it.n;
		}

		unsigned operator *() const;

		const_iterator &operator ++() noexcept {
			++n;
			return *this;
		}
	};

	const_iterator begin() const noexcept {
		return {*this, 0};
	}

	const_iterator end() const noexcept {
		return {*this, octets_num};
	}

	bool operator ==(ip_t const & ip) const noexcept {
		return octets == ip.octets;
	}

	bool operator >(ip_t const & ip) const noexcept {
		return octets > ip.octets;
	}
};

using ip_pool_t = std::vector<ip_t>;
using filter_t = std::function<bool(ip_t const &)>;

ip_str_t split(std::string const &str, char const d);
ip_pool_t parse(std::istream &i);
void issue(std::ostream &o, ip_pool_t const &ip_pool, filter_t const &filter);

#endif
