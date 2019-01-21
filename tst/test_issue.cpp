#include "lib.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <random>
#include <string>

TEST(GroupiLibrary, TestFunctionIssue) {
	enum: unsigned {attempts = 10};

	for (unsigned attempt{0}; attempt < attempts; attempt++) {
		enum: unsigned {lines = 128 * 1024};

		std::uniform_int_distribution<uint8_t> dist{std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max()};
		std::random_device rnd;

		auto const first{dist(rnd)};
		auto const second{dist(rnd)};
		auto const third{dist(rnd)};
		auto const fourth{dist(rnd)};

		auto const filter{[&](ip_t const &ip) {
			auto it{std::cbegin(ip)};

			return
				ip.at(0) == first  ||
				ip.at(1) == second ||
				ip.at(2) == third  ||
				ip.at(3) == fourth;
		}};

		ip_pool_t to_be_issued;
		ip_pool_t pool;

		for(unsigned line{0}; line < lines; line++) {
			ip_t ip{ip_str_t{
				std::to_string(dist(rnd)),
				std::to_string(dist(rnd)),
				std::to_string(dist(rnd)),
				std::to_string(dist(rnd))
			}
			};

			if (ip.at(0) == first || ip.at(1) == second || ip.at(2) == third || ip.at(3) == fourth) {
				to_be_issued.push_back(ip);
			}

			pool.push_back(ip);
		}

		std::ostringstream should_be_issued;
		std::ostringstream issued;

		for (auto const &ip: to_be_issued) {
			bool dot{};

			for (auto const &ip_part: ip) {
				should_be_issued << (dot ? "." : "") << static_cast<unsigned>(ip_part);
				dot = true;
			}

			should_be_issued << std::endl;
		}

		issue(issued, pool, filter);

		EXPECT_EQ(issued.str(), should_be_issued.str());
	}
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
