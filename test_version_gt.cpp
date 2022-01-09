#include <gtest/gtest.h>
#include "lib.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  ASSERT_GT(version(), 0);
  //EXPECT_EQ(7 * 6, 42);
}
