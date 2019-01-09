#include "lib.hpp"

#include <gtest/gtest.h>

#include <string>

TEST(Group1, Test1) {
	EXPECT_EQ(ver(), std::to_string(major()) + '.' + std::to_string(minor()) + '.' + std::to_string(patch()));
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
