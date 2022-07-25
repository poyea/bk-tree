#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class Distance_Identity_TEST : public ::testing::Test {
protected:
  Distance_Identity_TEST() {}

  virtual ~Distance_Identity_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::metrics::IdentityDistance dist;
};

TEST_F(Distance_Identity_TEST, IdentityDistances) {
  EXPECT_TRUE(dist("peter", "piter") == 1);
  EXPECT_TRUE(dist("peter", "pitar") == 1);
  EXPECT_TRUE(dist("peter", "pitat") == 1);
  EXPECT_TRUE(dist("ca", "abc") == 1);
  EXPECT_TRUE(dist("peter", "") == 1);
  EXPECT_TRUE(dist("", "peter") == 1);
  EXPECT_TRUE(dist("", "") == 1);
}

} // namespace bk_tree_test
