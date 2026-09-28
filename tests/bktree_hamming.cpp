#include "gtest/gtest.h"

#include "bktree.hpp"

namespace bk_tree_test {

class BKTree_Hamming_TEST : public ::testing::Test {
protected:
  BKTree_Hamming_TEST() {
    std::vector<std::string> input{"tall", "tell",  "teel",  "feel", "tally",
                                   "tuck", "belly", "kelly", "kill", "tal"};
    for (auto &s : input) {
      tree.insert(s);
    }
  }

  virtual ~BKTree_Hamming_TEST() {}

  virtual void SetUp() {
    // post-construction
  }

  virtual void TearDown() {
    // pre-destruction
  }

  bk_tree::BKTree<bk_tree::metrics::HammingDistance> tree;
  bk_tree::ResultList results;
};

TEST_F(BKTree_Hamming_TEST, TreeSize) { EXPECT_EQ(tree.size(), 6); }

TEST_F(BKTree_Hamming_TEST, TreeFindIncompatibleLength) {
  results = tree.find("too-long", std::numeric_limits<bk_tree::integer_type>::max());
  EXPECT_TRUE(results.empty());
}

TEST_F(BKTree_Hamming_TEST, TreeFind) {
  const std::string &word = "tale";
  for (bk_tree::integer_type limit = 1; limit <= 3; limit++) {
    results = tree.find(word, limit);
    for (auto &p : results) {
      EXPECT_TRUE(bk_tree::integer_type{1} <= p.second && p.second <= limit);
    }
  }
}

} // namespace bk_tree_test
