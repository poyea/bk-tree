#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class BKTree_Edit_TEST : public ::testing::Test {
protected:
  BKTree_Edit_TEST() {
    // Test adopted from: https://en.wikipedia.org/wiki/BK-tree#Example
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
  auto t1(tree);
  EXPECT_EQ(t1.size(), 9);

  auto t2 = tree;
  EXPECT_EQ(t2.size(), 9);

  bk_tree::BKTree<bk_tree::metrics::EditDistance> t3(tree), t4;
  t4 = t3;
  auto t5 = std::move(t3);
  EXPECT_EQ(t3.size(), 9);
  EXPECT_EQ(t4.size(), 9);
  EXPECT_EQ(t5.size(), 9);

  const std::string &word = "book";
  results = t5.find(word, 1);
  for (auto &p : results) {
    EXPECT_TRUE(1 >= p.second);
    EXPECT_TRUE(p.first == "books" || p.first == "boo" || p.first == "boon" ||
                p.first == "cook" || p.first == "book");
  }
}

} // namespace bk_tree_test
