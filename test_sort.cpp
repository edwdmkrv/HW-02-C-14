#include "lib.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <random>
#include <string>

TEST(GroupiLibrary, TestFunctionSort) {
	enum: unsigned {attempts = 10};

	for (unsigned attempt{0}; attempt < attempts; attempt++) {
		enum: unsigned {lines = 64 * 1024};

		std::uniform_int_distribution<uint8_t> dist{std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max()};
		std::random_device rnd;

		std::vector<uint32_t> ips;

		for (unsigned line{0}; line < lines; line++) {
			ips.emplace_back(dist(rnd) + dist(rnd) * 256u + dist(rnd) * 256u * 256 + dist(rnd) * 256u * 256 * 256);
		}

		auto const convert{[&] {
			ip_pool_t pool;

			for (unsigned line{0}; line < lines; line++) {
				uint32_t const ip{ips.at(line)};

				pool.emplace_back(
					ip_t{
						std::to_string(ip / 256 / 256 / 256),
						std::to_string(ip / 256 / 256 % 256),
						std::to_string(ip / 256 % 256),
						std::to_string(ip % 256)
					}
				);
			}

			return pool;
		}};

		ip_pool_t to_be_sorted{convert()};

		std::sort(std::begin(ips), std::end(ips), std::greater<uint32_t>{});

		ip_pool_t const sorted{convert()};

		sort(to_be_sorted);

		EXPECT_EQ(to_be_sorted, sorted);
	}
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
