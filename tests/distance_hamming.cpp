#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class Distance_Hamming_TEST : public ::testing::Test {
protected:
  Distance_Hamming_TEST() {}

  virtual ~Distance_Hamming_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::metrics::HammingDistance dist;
};

TEST_F(Distance_Hamming_TEST, HammingDistances) {
  EXPECT_TRUE(dist("peter", "piter") == 1);
  EXPECT_TRUE(dist("peter", "pitar") == 2);
  EXPECT_TRUE(dist("peter", "pitat") == 3);
  EXPECT_TRUE(dist("peter", "") ==
              std::numeric_limits<bk_tree::IntegerType>::max());
  EXPECT_TRUE(dist("", "peter") ==
              std::numeric_limits<bk_tree::IntegerType>::max());
  EXPECT_TRUE(dist("", "") == 0);
}

} // namespace bk_tree_test
