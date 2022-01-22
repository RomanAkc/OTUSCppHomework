#include <gtest/gtest.h>
#include "ip_filter_lib.h"

// Demonstrate some basic assertions.
TEST(filter_test, BasicAssertions) {
	IPPool ipPool = {
		std::vector<std::string> {"1", "1", "1", "1"}, 
		std::vector<std::string> {"2", "1", "1", "1"}, 
		std::vector<std::string> {"1", "2", "1", "1"}, 
		std::vector<std::string> {"1", "10", "1", "1"}, 
	};

	reverseLexicographicallySort(ipPool);

	auto result1 = filter(ipPool, 2);
	EXPECT_EQ(result1.size(), 1);

	auto result2 = filter(ipPool, 1);
	EXPECT_EQ(result2.size(), 3);

	auto result3 = filter_any(ipPool, 2);
	EXPECT_EQ(result3.size(), 2);

	auto result4 = filter_any(ipPool, 1);
	EXPECT_EQ(result4.size(), 4);
}