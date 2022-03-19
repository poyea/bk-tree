#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class BKTree_Edit_TEST : public ::testing::Test {
protected:
  BKTree_Edit_TEST() {
    std::vector<std::string> input{"book", "books", "cake", "boo", "boon",
                                   "cook", "cake",  "cape", "cart"};
    for (auto &s : input) {
      tree.insert(s);
    }
  }

  virtual ~BKTree_Edit_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::BKTree<bk_tree::metrics::EditDistance> tree;
  bk_tree::ResultList results;
};

TEST_F(BKTree_Edit_TEST, TreeSize) { EXPECT_EQ(tree.size(), 9); }

TEST_F(BKTree_Edit_TEST, TreeFind) {
  const std::string &word = "book";
  results = tree.find(word, 1);
  for (auto &p : results) {
    EXPECT_TRUE(1 >= p.second);
    EXPECT_TRUE(p.first == "books" || p.first == "boo" || p.first == "boon" ||
                p.first == "cook" || p.first == "book");
  }
}

} // namespace bk_tree_test
