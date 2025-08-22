#include "gtest/gtest.h"
#include "logger/logger.h"
#include <iostream>

#define GIVEN "\033[34mGIVEN\033[0m "
#define WHEN  "\033[34mWHEN\033[0m  "
#define THEN  "\033[34mTHEN\033[0m  "

TEST(logger_unittest, dummy_test)
{
	std::cout << GIVEN << "\n";
	std::cout << WHEN << "\n";
	std::cout << THEN << "\n";
	ASSERT_TRUE(true);
}
