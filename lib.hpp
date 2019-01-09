#ifndef __LIB_INCLUDED
#define __LIB_INCLUDED

#include <string>
#include <vector>
#include <functional>
#include <iostream>

std::string ver();

unsigned major();
unsigned minor();
unsigned patch();

using ip_t = std::vector<std::string>;
using ip_pool_t = std::vector<ip_t>;
using filter_t = std::function<bool(ip_t const &)>;

ip_t split(std::string const &str, char const d);
ip_pool_t parse(std::istream &i);
void sort(ip_pool_t &ip_pool);
void issue(std::ostream &o, ip_pool_t const &ip_pool, filter_t const &filter);

#endif
