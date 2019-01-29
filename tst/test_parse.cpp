#include "lib.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <random>
#include <string>

struct Data {
	std::string const stream;
	ip_pool_t const expected;

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
		<< "stream: \"" << data.stream << "\", "
		<< "expected: " << data.expected;
}

struct TestLibrary: testing::Test, testing::WithParamInterface<Data> {
};

TEST_P(TestLibrary, TestFunctionSplit) {
	Data const data{GetParam()};
	std::istringstream i{data.stream};

	auto const ip_pool{parse(i)};

	EXPECT_EQ(ip_pool, data.expected);
}

INSTANTIATE_TEST_CASE_P(SimpleDataset, TestLibrary,
	testing::Values(
		Data{
			"1.2.3.4\taaa\tbbb\n5.6.7.8\t\n9.10.11.12",
			{ip_str_t{"1", "2", "3", "4"}, ip_str_t{"5", "6", "7", "8"}, ip_str_t{"9", "10", "11", "12"}},
		},
		Data{
			"1.2.3.4\n5.6.7.8\n9.10.11.12",
			{ip_str_t{"1", "2", "3", "4"}, ip_str_t{"5", "6", "7", "8"}, ip_str_t{"9", "10", "11", "12"}},
		}
	)
);

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
