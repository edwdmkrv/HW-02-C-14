#include "lib.hpp"

#include <gtest/gtest.h>

#include <iostream>

TEST(Group1, Test1) {
	EXPECT_TRUE(static_cast<bool>(std::cout << "Version: " << ver() << std::endl));
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
