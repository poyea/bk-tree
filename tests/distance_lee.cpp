#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class Distance_Lee_TEST : public ::testing::Test {
protected:
  Distance_Lee_TEST() : dist(3) {}

  virtual ~Distance_Lee_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  void set_alphabet_size(int size) {
    dist = bk_tree::metrics::LeeDistance(size);
  }

  bk_tree::metrics::LeeDistance dist;
  bk_tree::metrics::HammingDistance hamming_dist;
};

TEST_F(Distance_Lee_TEST, LeeDistances) {
  EXPECT_TRUE(dist("peter", "") ==
              std::numeric_limits<bk_tree::IntegerType>::max());
  EXPECT_TRUE(dist("", "peter") ==
              std::numeric_limits<bk_tree::IntegerType>::max());

  EXPECT_TRUE(dist("abcde", "ace") == hamming_dist("abcde", "ace"));
  EXPECT_TRUE(dist("abcde", "abcde") == hamming_dist("abcde", "abcde"));
  EXPECT_TRUE(dist("ace", "ace") == hamming_dist("ace", "ace"));

  set_alphabet_size(6);
  EXPECT_TRUE(dist("3140", "2543") == 6);
}

} // namespace bk_tree_test
