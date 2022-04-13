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

TEST_F(BKTree_Base_TEST, TreeErase) {
  const std::string &word = "word";
  tree.insert(word);
  tree.erase(word);
  EXPECT_TRUE(tree.empty());

  const std::string &wordy = "wordy";
  tree.insert(word);
  tree.insert(wordy);
  tree.erase(word);
  EXPECT_TRUE(tree.size() == 1);
}

} // namespace bk_tree_test
