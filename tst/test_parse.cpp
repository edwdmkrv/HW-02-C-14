#include "lib.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <random>
#include <string>

TEST(GroupiLibrary, TestFunctionParse) {
	enum: unsigned {attempts = 10};

	for (unsigned attempt{0}; attempt < attempts; attempt++) {
		enum: unsigned {lines = 4 * 1024};

		std::uniform_int_distribution<char> dist{std::numeric_limits<char>::min(), std::numeric_limits<char>::max()};
		std::random_device rnd;

		std::string str;
		std::string eth_str;
		ip_str_t eth_ip;
		ip_pool_t ethalon;

		unsigned line{0};
		bool eth_filled{false};

		while (line < lines) {
			char const d{dist(rnd)};

			bool const tab = d == '\t';
			bool const eol = d == '\n';
			bool const dot = d == '.';

			str += d;

			if (!eth_filled) {
				if (!tab && !eol) {
					if (!dot) {
						eth_str += d;
					} else {
						eth_ip.emplace_back();
						std::swap(eth_str, eth_ip.back());
					}
				} else {
					eth_ip.emplace_back();
					std::swap(eth_str, eth_ip.back());

					ethalon.emplace_back();
					std::swap(eth_ip, ethalon.back());
					goto fix_eth_filled;
				}
			} else {
fix_eth_filled:
				eth_filled = !eol;
			}

			line += eol;
		}

		std::istringstream stream{str};
		ip_pool_t const parsed{parse(stream)};

		EXPECT_EQ(parsed, ethalon);
	}
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
