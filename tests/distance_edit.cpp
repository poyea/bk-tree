#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class Distance_Edit_TEST : public ::testing::Test {
protected:
  Distance_Edit_TEST() {}

  virtual ~Distance_Edit_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::metrics::EditDistance dist;
};

TEST_F(Distance_Edit_TEST, EditDistances) {
  EXPECT_TRUE(dist("peter", "piter") == 1);
  EXPECT_TRUE(dist("peter", "pitar") == 2);
  EXPECT_TRUE(dist("peter", "pita") == 3);
  EXPECT_TRUE(dist("kitten", "sitting") == 3);
  EXPECT_TRUE(dist("ab", "abc") == 1);
  EXPECT_TRUE(dist("stall", "table") == 3);
  EXPECT_TRUE(dist("peter", "") == 5);
  EXPECT_TRUE(dist("", "peter") == 5);
  EXPECT_TRUE(dist("", "") == 0);
}

} // namespace bk_tree_test
