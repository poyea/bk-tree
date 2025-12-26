#include "bktree.hpp"
#include <iostream>
#include <string>
#include <vector>

void example() {
  bk_tree::BKTree<bk_tree::metrics::HammingDistance> tree;
  {
    std::vector<std::string> input{"tall", "tell",  "teel",  "feel", "tally",
                                   "tuck", "belly", "kelly", "kill", "tal"};
    for (auto &s : input) {
      tree.insert(s);
    }
  }

  std::cout << "Tree size: " << tree.size() << std::endl << std::endl;

  bk_tree::ResultList results;
  auto target = "tale";
  for (int limit = 1; limit <= 3; limit++) {
    std::cout << "Limit: " << limit << std::endl;
    results = tree.find(target, limit);
    for (auto &p : results) {
      std::cout << p.first << " " << p.second << std::endl;
    }
    std::cout << std::endl;
  }
}

int main() {
  example();
  return 0;
}
