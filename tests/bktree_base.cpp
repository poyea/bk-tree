#include "gtest/gtest.h"

#include "bktree.hpp"
#include <set>

namespace bk_tree_test {

class LargeDistance final : public bk_tree::metrics::Distance<LargeDistance> {
public:
  bk_tree::integer_type compute_distance(std::string_view s,
                                         std::string_view t) const noexcept {
    return s == t ? 0 : (bk_tree::integer_type{1} << 40);
  }
};

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
  results = tree.find("word", 1);
  EXPECT_TRUE(results.empty());
}

TEST_F(BKTree_Base_TEST, TreeFindLargeDistance) {
  constexpr bk_tree::integer_type large_distance = bk_tree::integer_type{1} << 40;
  bk_tree::BKTree<LargeDistance> large_tree;
  EXPECT_TRUE(large_tree.insert("root"));
  EXPECT_TRUE(large_tree.insert("leaf"));

  results = large_tree.find("leaf", large_distance);
  ASSERT_EQ(results.size(), 2);
  EXPECT_EQ(results[0].first, "root");
  EXPECT_EQ(results[0].second, large_distance);
  EXPECT_EQ(results[1].first, "leaf");
  EXPECT_EQ(results[1].second, 0);
  EXPECT_TRUE(large_tree.find("leaf", -1).empty());
}

TEST_F(BKTree_Base_TEST, TreeWithList) {
  tree = {"word", "tree", "wordy", "stuff"};
  EXPECT_TRUE(tree.size() == 4);
}

TEST_F(BKTree_Base_TEST, TreeEraseEmpty) {
  EXPECT_FALSE(tree.erase("nonexistentrandomword"));
}

TEST_F(BKTree_Base_TEST, TreeEraseSingle) {
  tree.insert("word");
  EXPECT_TRUE(tree.erase("word"));
  EXPECT_TRUE(tree.empty());
}

TEST_F(BKTree_Base_TEST, TreeEraseRoot) {
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

TEST_F(BKTree_Base_TEST, TreeEraseRootNary) {
  {
    std::string s1{"word"};
    std::string s2{"wordy"};
    std::string s3{"wordo"};
    std::string s4{"worda"};
    tree.insert(s1);
    tree.insert(s2);
    tree.insert(s3);
    tree.insert(s4);
  }

  for (auto const &node : tree) {
    EXPECT_TRUE(node->word().length() <= 5 and not node->word().empty());
  }

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    EXPECT_TRUE((*it)->word().length() <= 5 and not(*it)->word().empty());
  }

  for (auto it = tree.begin(); it != tree.end(); it++) {
    EXPECT_TRUE((*it)->word().length() <= 5 and not(*it)->word().empty());
  }

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

  tree.erase("worda");
  EXPECT_TRUE(tree.size() == 1);
  results = tree.find("word", 1);
  set_of_strings = {"wordy"};
  for (auto const &p : results) {
    set_of_strings.erase(p.first);
  }
  EXPECT_TRUE(set_of_strings.size() == 0);
  EXPECT_TRUE(results.size() == 1);

  tree.erase("wordy");
  EXPECT_TRUE(tree.size() == 0);
  tree.erase("wordy");
  EXPECT_TRUE(tree.size() == 0);

  results = tree.find("word", 1);
  EXPECT_TRUE(set_of_strings.size() == 0);
  EXPECT_TRUE(results.size() == 0);
}

} // namespace bk_tree_test
