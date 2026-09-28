#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class Distance_LCSubseq_TEST : public ::testing::Test {
protected:
  Distance_LCSubseq_TEST() {}

  virtual ~Distance_LCSubseq_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::metrics::LCSubseqDistance dist;
  bk_tree::metrics::EditDistance edit_dist;
};

TEST_F(Distance_LCSubseq_TEST, LCSubseqDistances) {
  EXPECT_TRUE(dist("ABCD", "ACBAD") == 3);
  EXPECT_TRUE(dist("ABCD", "AEFG") == 6);
  EXPECT_TRUE(dist("", "") == 0);
  EXPECT_TRUE(dist("a", "a") == 0);
  EXPECT_TRUE(dist("abcde", "ace") == 2);
  EXPECT_TRUE(dist("abcde", "abcde") == 0);
  EXPECT_TRUE(dist("peter", "") == 5);
  EXPECT_TRUE(dist("abcde", "fghij") == 10);
  EXPECT_TRUE(dist("a", "b") == 2);

  EXPECT_EQ(dist("abcde", "ace"), edit_dist("abcde", "ace"));
  EXPECT_EQ(dist("abcde", "abcde"), edit_dist("abcde", "abcde"));

  bk_tree::BKTree<bk_tree::metrics::LCSubseqDistance> tree;
  tree.insert("same");
  tree.insert("some");
  EXPECT_EQ(tree.find("same", 0).size(), 1);
}

} // namespace bk_tree_test
