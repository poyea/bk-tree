<img align="left" width="150" height="150" src="https://user-images.githubusercontent.com/24757020/150530071-e3792d5e-700b-4e50-84fe-9948b3afe8fa.png" alt="Palm Tree">

# bk-tree ![CMake](https://github.com/poyea/bk-tree/workflows/CMake/badge.svg)

Header-only Burkhard-Keller tree implementation in C++, with minimal examples.

<br/>

## Example

```cpp
#include "bktree.hpp"
#include <iostream>

int main() {
  using metric_t = bk_tree::metrics::DamerauLevenshteinDistance;
  using tree_t = bk_tree::BKTree<metric_t>;
  tree_t tree;

  tree.insert("tall");
  tree.insert("tell");
  tree.insert("teel");
  tree.insert("feel");

  std::cout << "Tree size: " << tree.size() << std::endl; // Tree size: 4

  auto result = tree.find("tale", 1);
  for (auto &p : result) {
    std::cout << p.first << " " << p.second << std::endl; // tall 1
  }
}
```

## License
This repository is licensed under The GNU General Public License v3.0. See also [LICENSE](LICENSE) for details.

## References

Fred J. Damerau. 1964. A technique for computer detection and correction of spelling errors. Communications of the ACM 7, 3 (1964), 171–176. DOI:http://dx.doi.org/10.1145/363958.363994 

Vladimir I. Levenshtein. 1966. Binary codes capable of correcting deletions, insertions, and reversals. Soviet physics doklady 10, 8 (1966), 845-848.

W.A. Burkhard and R.M. Keller. 1973. Some approaches to best-match file searching. Communications of the ACM 16, 4 (1973), 230–236. DOI:http://dx.doi.org/10.1145/362003.362025 
