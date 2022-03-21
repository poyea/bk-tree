#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class BKTree_Base_TEST : public ::testing::Test {
protected:
  BKTree_Base_TEST() = default;

  virtual ~BKTree_Base_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::BKTree<bk_tree::metrics::EditDistance> tree;
  bk_tree::ResultList results;
};

TEST_F(BKTree_Base_TEST, TreeSize) { EXPECT_EQ(tree.size(), 0); }

TEST_F(BKTree_Base_TEST, TreeFind) {
  const std::string &word = "word";
  results = tree.find(word, 1);
  EXPECT_TRUE(results.empty());
}

} // namespace bk_tree_test
