#include "lib.hpp"

#include <gtest/gtest.h>

#include <iostream>

TEST(GroupiLibrary, TestFunctionIssue) {
	EXPECT_TRUE(true);
}

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
