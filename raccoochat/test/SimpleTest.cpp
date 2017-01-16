#include <vector>

#include <gtest/gtest.h>

TEST(SimpleTest, simple) {
  std::vector<int> a {1, 2, 3};
  EXPECT_EQ(a.size(), 3);
}
