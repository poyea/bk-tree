#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class Distance_Length_TEST : public ::testing::Test {
protected:
  Distance_Length_TEST() {}

  virtual ~Distance_Length_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::metrics::LengthDistance dist;
};

TEST_F(Distance_Length_TEST, LengthDistances) {
  EXPECT_TRUE(dist("", "") == 0);
  EXPECT_TRUE(dist("peter", "piter") == 0);
  EXPECT_TRUE(dist("peter", "pitar") == 0);
  EXPECT_TRUE(dist("peter", "pitat") == 0);
  EXPECT_TRUE(dist("ca", "abc") == 1);
  EXPECT_TRUE(dist("peter", "") == 5);
  EXPECT_TRUE(dist("", "peter") == 5);
}

} // namespace bk_tree_test
