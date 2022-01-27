#include "bktree.hpp"
#include <iostream>
#include <string>
#include <vector>

void example1() {
  bk_tree::BKTree<bk_tree::metrics::HammingDistance> tree;
  std::vector<std::string> input{"tall", "tell",  "teel",  "feel", "tally",
                                 "tuck", "belly", "kelly", "kill", "tal"};
  for (auto &s : input) {
    tree.insert(s);
  }
  std::cout << "Tree size: " << tree.size() << std::endl << std::endl;
  bk_tree::ResultList results;
  for (int limit = 1; limit <= 3; limit++) {
    std::cout << "Limit: " << limit << std::endl;
    results = tree.find("tale", limit);
    for (auto &p : results) {
      std::cout << p.first << " " << p.second << std::endl;
    }
    std::cout << std::endl;
  }
}

void example2() {
  bk_tree::BKTree<bk_tree::metrics::EditDistance> tree;
  std::vector<std::string> input{"tall", "tell",  "teel",  "feel", "tally",
                                 "tuck", "belly", "kelly", "kill", "tal"};
  for (auto &s : input) {
    tree.insert(s);
  }
  std::cout << "Tree size: " << tree.size() << std::endl << std::endl;
  bk_tree::ResultList results;
  for (int limit = 1; limit <= 3; limit++) {
    std::cout << "Limit: " << limit << std::endl;
    results = tree.find("tale", limit);
    for (auto &p : results) {
      std::cout << p.first << " " << p.second << std::endl;
    }
    std::cout << std::endl;
  }
}

void example3() {
  bk_tree::BKTree<bk_tree::metrics::DamerauLevenshteinDistance> tree;
  std::vector<std::string> input{"tall", "tell",  "teel",  "feel", "tally",
                                 "tuck", "belly", "kelly", "kill", "tal"};
  for (auto &s : input) {
    tree.insert(s);
  }
  std::cout << "Tree size: " << tree.size() << std::endl << std::endl;
  std::cout << "Can erase 'tell'? " << std::boolalpha << tree.erase("tell")
            << std::endl;
  std::cout << "Size after erase: " << tree.size() << std::endl << std::endl;
  std::cout << "Can erase 'tall'? " << std::boolalpha << tree.erase("tall")
            << std::endl;
  std::cout << "Size after erase: " << tree.size() << std::endl << std::endl;
}

int main() {
  int N = -1;
  while (1) {
    std::cin >> N;
    switch (N) {
    case 1:
      example1();
      break;
    case 2:
      example2();
      break;
    case 3:
      example3();
      break;
    default:
      return 0;
    }
  }
  return 0;
}
