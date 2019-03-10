#include "lib.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <random>
#include <string>

struct Data {
	filter_t const filter;
	std::string const filt_str;
	ip_pool_t const ip_pool;
	std::string const expected;

};

std::ostream &operator <<(std::ostream &o, ip_pool_t const &ip_pool) {
	bool first{true};

	o << '{';

	for (auto const &ip: ip_pool) {
		o << (first ? "" : ", ") << ip;
		first = false;
	}

	return o << '}';
}

std::ostream &operator <<(std::ostream &o, Data const &data) {
	return o
		<< "filter: '" << data.filt_str << "', "
		<< "ip pool: \"" << data.ip_pool << "\", "
		<< "expected: " << data.expected;
}

struct TestLibrary: testing::Test, testing::WithParamInterface<Data> {
};

TEST_P(TestLibrary, TestFunctionSplit) {
	Data const data{GetParam()};
	std::ostringstream o;

	o << ip_pool_filtered_proxy_t{data.ip_pool, data.filter};

	EXPECT_EQ(o.str(), data.expected);
}

INSTANTIATE_TEST_CASE_P(SimpleDataset, TestLibrary,
	testing::Values(
		Data{
			[](ip_t const &) {return true;},
			"true",
			{ip_str_t{"1", "2", "3", "4"}, ip_str_t{"5", "6", "7", "8"}, ip_str_t{"9", "10", "11", "12"}},
			"1.2.3.4\n5.6.7.8\n9.10.11.12\n"
		},
		Data{
			[](ip_t const &ip) {return ip.at(0) == 1;},
			"ip.at(0) == 1",
			{ip_str_t{"1", "2", "3", "4"}, ip_str_t{"5", "6", "7", "8"}, ip_str_t{"9", "10", "11", "12"}},
			"1.2.3.4\n"
		},
		Data{
			[](ip_t const &ip) {return ip.at(0) == 46 && ip.at(1) == 70;},
			"ip.at(0) == 46 && ip.at(1) == 70",
			{ip_str_t{"1", "70", "3", "4"}, ip_str_t{"46", "70", "7", "8"}, ip_str_t{"46", "10", "11", "12"}},
			"46.70.7.8\n"
		},
		Data{
			[](ip_t const &ip) {return ip.at(0) == 46 || ip.at(1) == 46 || ip.at(2) == 46 || ip.at(3) == 46;},
			"ip.at(0) == 46 || ip.at(1) == 46 || ip.at(2) == 46 || ip.at(3) == 46",
			{ip_str_t{"1", "70", "3", "4"}, ip_str_t{"46", "70", "7", "8"}, ip_str_t{"46", "10", "11", "12"}},
			"46.70.7.8\n46.10.11.12\n"
		}
	)
);

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
