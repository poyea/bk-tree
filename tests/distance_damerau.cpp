#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class Distance_DamerauLevenshtein_TEST : public ::testing::Test {
protected:
  Distance_DamerauLevenshtein_TEST() {}

  virtual ~Distance_DamerauLevenshtein_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::metrics::DamerauLevenshteinDistance dist;
};

TEST_F(Distance_DamerauLevenshtein_TEST, DamerauLevenshteinDistances) {
  EXPECT_TRUE(dist("peter", "piter") == 1);
  EXPECT_TRUE(dist("peter", "pitar") == 2);
  EXPECT_TRUE(dist("peter", "pitat") == 3);
  EXPECT_TRUE(dist("ca", "abc") == 3);
  EXPECT_TRUE(dist("peter", "") == 5);
  EXPECT_TRUE(dist("", "peter") == 5);
  EXPECT_TRUE(dist("", "") == 0);
}

} // namespace bk_tree_test
