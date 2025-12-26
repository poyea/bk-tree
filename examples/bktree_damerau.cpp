#include "bktree.hpp"
#include <iostream>
#include <string>
#include <vector>

void example() {
  bk_tree::BKTree<bk_tree::metrics::DamerauLevenshteinDistance> tree;
  {
    std::vector<std::string> input{"tall", "tell",  "teel",  "feel", "tally",
                                   "tuck", "belly", "kelly", "kill", "tal"};
    for (auto &s : input) {
      tree.insert(s);
    }
  }

  for (auto const &node : tree) {
    std::cout << node->word() << ' ';
  }
  std::cout << '\n';

  std::cout << "Tree size: " << tree.size() << std::endl << std::endl;
  std::cout << "Can erase 'tell'? " << std::boolalpha << tree.erase("tell")
            << std::endl;
  std::cout << "Size after erase: " << tree.size() << std::endl << std::endl;
  std::cout << "Can erase 'tall'? " << std::boolalpha << tree.erase("tall")
            << std::endl;
  std::cout << "Size after erase: " << tree.size() << std::endl << std::endl;
}

int main() {
  example();
  return 0;
}
