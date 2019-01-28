#include "lib.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <random>
#include <string>

struct Data {
	char const delimiter;
	std::string const string;
	ip_str_t const expected;

};

std::ostream &operator <<(std::ostream &o, ip_str_t const &ip_str) {
	bool first{true};

	o << '{';

	for (auto const &str: ip_str) {
		o << (first ? "" : ", ") << '"' << str << '"';
		first = false;
	}

	return o << '}';
}

std::ostream &operator <<(std::ostream &o, Data const &data) {
	return o
		<< "delimiter: '" << data.delimiter << "', "
		<< "string: \"" << data.string << "\", "
		<< "expected: " << data.expected;
}

struct TestLibrary: testing::Test, testing::WithParamInterface<Data> {
};

TEST_P(TestLibrary, TestFunctionSplit) {
	Data const data{GetParam()};

	EXPECT_EQ(split(data.string, data.delimiter), data.expected);
}

INSTANTIATE_TEST_CASE_P(SimpleDataset, TestLibrary,
	testing::Values(
		Data{'.', "1.2.3.4", {"1", "2", "3", "4"}},
		Data{'.', "1...4", {"1", "", "", "4"}},
		Data{' ', "This is a text", {"This", "is", "a", "text"}},
		Data{' ', "This is a very long text", {"This", "is", "a", "very", "long", "text"}},
		Data{'\n', "The first line\n\nThe third line", {"The first line", "", "The third line"}}
	)
);

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
