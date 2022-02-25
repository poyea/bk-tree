#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class Distance_LCS_TEST : public ::testing::Test {
protected:
  Distance_LCS_TEST() {}

  virtual ~Distance_LCS_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::metrics::LCSDistance dist;
  bk_tree::metrics::EditDistance edit_dist;
};

TEST_F(Distance_LCS_TEST, LCSDistances) {
  EXPECT_TRUE(dist("ABCD", "ACBAD") == 3);
  EXPECT_TRUE(dist("", "") == 0);
  EXPECT_TRUE(dist("a", "a") == 1);
  EXPECT_TRUE(dist("abcde", "ace") == 3);
  EXPECT_TRUE(dist("abcde", "abcde") == 5);
  EXPECT_TRUE(dist("peter", "") == 0);
  EXPECT_TRUE(dist("abcde", "fghij") == 0);
  EXPECT_TRUE(dist("a", "b") == 0);

  EXPECT_TRUE(3 + 5 - 2 * dist("abcde", "ace") == edit_dist("abcde", "ace"));
  EXPECT_TRUE(5 + 5 - 2 * dist("abcde", "abcde") ==
              edit_dist("abcde", "abcde"));
}

} // namespace bk_tree_test
