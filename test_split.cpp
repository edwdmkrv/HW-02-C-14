#include "lib.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <random>
#include <string>

TEST(TestLibrary, TestFunctionSplit) {
	enum: unsigned {attempts = 10};

	for (unsigned attempt{0}; attempt < attempts; attempt++) {
		enum: std::size_t {len = 1024 * 1024};
	
		std::uniform_int_distribution<char> dist{std::numeric_limits<char>::min(), std::numeric_limits<char>::max()};
		std::random_device rnd;
	
		std::string str;
		std::vector<std::string> ethalon{{}};
	
		char const d{dist(rnd)};
	
		for (std::size_t n{0}; n < len; n++) {
			char const sym{dist(rnd)};
	
			str += sym;
	
			if (sym != d) {
				ethalon.back() += sym;
			} else {
				ethalon.push_back({});
			}
		}
	
		std::vector<std::string> const splitted{split(str, d)};
		std::cout << "size: " << splitted.size() << std::endl;
	
		EXPECT_EQ(splitted, ethalon);
	}
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
