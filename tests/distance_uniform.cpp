#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class Distance_Uniform_TEST : public ::testing::Test {
protected:
  Distance_Uniform_TEST() {}

  virtual ~Distance_Uniform_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::metrics::UniformDistance dist;
};

TEST_F(Distance_Uniform_TEST, UniformDistances) {
  EXPECT_TRUE(dist("peter", "piter") == 1);
  EXPECT_TRUE(dist("peter", "pitar") == 1);
  EXPECT_TRUE(dist("peter", "pitat") == 1);
  EXPECT_TRUE(dist("ca", "abc") == 1);
  EXPECT_TRUE(dist("peter", "") == 1);
  EXPECT_TRUE(dist("", "peter") == 1);
  EXPECT_TRUE(dist("", "") == 1);
}

} // namespace bk_tree_test
