#include "gtest/gtest.h"

#include "bktree.hpp"
#include <set>

namespace bk_tree_test {

class BKTree_Uniform_TEST : public ::testing::Test {
protected:
  BKTree_Uniform_TEST() = default;

  virtual ~BKTree_Uniform_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::BKTree<bk_tree::metrics::UniformDistance> tree;
  bk_tree::ResultList results;
};

TEST_F(BKTree_Uniform_TEST, TreeSize) { EXPECT_EQ(tree.size(), 0); }

TEST_F(BKTree_Uniform_TEST, TreeFind) {
  results = tree.find("word", 1);
  EXPECT_TRUE(results.empty());
}

TEST_F(BKTree_Uniform_TEST, TreeEraseSingle) {
  tree.insert("word");
  tree.erase("word");
  EXPECT_TRUE(tree.empty());
}

TEST_F(BKTree_Uniform_TEST, TreeEraseRoot) {
  tree.insert("word");
  tree.insert("wordy");
  tree.erase("word");
  EXPECT_TRUE(tree.size() == 1);
  results = tree.find("wordy", 1);
  EXPECT_TRUE(results.size() == 1);

  tree.erase("wordy");
  EXPECT_TRUE(tree.size() == 0);
  results = tree.find("wordy", 1);
  EXPECT_TRUE(results.size() == 0);
}

TEST_F(BKTree_Uniform_TEST, TreeEraseRootNary) {
  tree.insert("word");
  tree.insert("wordy");
  tree.insert("wordo");
  tree.insert("worda");
  EXPECT_TRUE(tree.size() == 4);
  results = tree.find("word", 1);
  EXPECT_TRUE(results.size() == 4);

  tree.erase("word");
  EXPECT_TRUE(tree.size() == 3);
  results = tree.find("word", 1);
  std::set<std::string_view> set_of_strings;
  set_of_strings = {"wordy", "wordo", "worda"};
  for (auto const &p : results) {
    set_of_strings.erase(p.first);
  }
  EXPECT_TRUE(set_of_strings.size() == 0);
  EXPECT_TRUE(results.size() == 3);

  tree.erase("wordo");
  EXPECT_TRUE(tree.size() == 2);
  results = tree.find("word", 1);
  set_of_strings = {"wordy", "worda"};
  for (auto const &p : results) {
    set_of_strings.erase(p.first);
  }
  EXPECT_TRUE(set_of_strings.size() == 0);
  EXPECT_TRUE(results.size() == 2);
}

} // namespace bk_tree_test
