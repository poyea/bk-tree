//
// bk-tree   Header-only Burkhard-Keller tree library
// Copyright (C) 2020-2022  John Law
//
// bk-tree is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// bk-tree is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with bk-tree.  If not, see <https://www.gnu.org/licenses/>.
//

#pragma once

#ifndef BK_MATRIX_INITIAL_SIZE
#define BK_MATRIX_INITIAL_SIZE 0
#endif
#ifndef BK_LCS_MATRIX_INITIAL_SIZE
#define BK_LCS_MATRIX_INITIAL_SIZE BK_MATRIX_INITIAL_SIZE
#endif
#ifndef BK_ED_MATRIX_INITIAL_SIZE
#define BK_ED_MATRIX_INITIAL_SIZE BK_MATRIX_INITIAL_SIZE
#endif
#ifndef BK_TREE_INITIAL_SIZE
#define BK_TREE_INITIAL_SIZE 0
#endif
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace bk_tree {

using IntegerType = std::uint64_t;

namespace metrics {

///
/// Lee distance metric
///
class LeeDistance {
  IntegerType m_alphabet_size;

public:
  explicit LeeDistance(IntegerType alphabet_size)
      : m_alphabet_size(alphabet_size){};
  IntegerType operator()(const std::string &s, const std::string &t) const {
    const IntegerType M = s.size(), N = t.size();
    if (M != N) {
      return std::numeric_limits<IntegerType>::max();
    }
    const IntegerType m_comparsion_size = M;
    IntegerType counter = 0, diff;
    for (IntegerType i = 0; i < m_comparsion_size; ++i) {
      diff = std::abs(s[i] - t[i]);
      counter += std::min(diff, m_alphabet_size - diff);
    }
    return counter;
  }
};

///
/// Longest Common Subsequence distance metric
///
class LCSDistance {
  mutable std::vector<std::vector<int>> m_matrix;

public:
  explicit LCSDistance(size_t initial_size = BK_LCS_MATRIX_INITIAL_SIZE)
      : m_matrix(initial_size, std::vector<int>(initial_size)){};
  IntegerType operator()(const std::string &s, const std::string &t) const {
    const IntegerType M = s.size(), N = t.size();
    if (M == 0 || N == 0) {
      return 0;
    }
    if (m_matrix.size() <= M || m_matrix[0].size() <= N) {
      std::vector<std::vector<int>> a_matrix(M + 1, std::vector<int>(N + 1));
      m_matrix.swap(a_matrix);
    }
    for (IntegerType i = 1; i <= M; ++i) {
      for (IntegerType j = 1; j <= N; ++j) {
        if (s[i - 1] == t[j - 1]) {
          m_matrix[i][j] = m_matrix[i - 1][j - 1] + 1;
        } else {
          m_matrix[i][j] = std::max(m_matrix[i - 1][j], m_matrix[i][j - 1]);
        }
      }
    }
    return m_matrix[M][N];
  }
};

///
/// Hamming distance metric
///
class HammingDistance {
public:
  explicit HammingDistance() = default;
  IntegerType operator()(const std::string &s, const std::string &t) const {
    const IntegerType M = s.size(), N = t.size();
    if (M != N) {
      return std::numeric_limits<IntegerType>::max();
    }
    const IntegerType m_comparsion_size = M;
    IntegerType counter = 0;
    for (IntegerType i = 0; i < m_comparsion_size; ++i) {
      counter += (s[i] != t[i]);
    }
    return counter;
  }
};

///
/// Edit distance metric
///
class EditDistance {
  mutable std::vector<std::vector<int>> m_matrix;

public:
  explicit EditDistance(size_t initial_size = BK_ED_MATRIX_INITIAL_SIZE)
      : m_matrix(initial_size, std::vector<int>(initial_size)){};
  IntegerType operator()(const std::string &s, const std::string &t) const {
    const IntegerType M = s.size(), N = t.size();
    if (M == 0 || N == 0) {
      return N + M;
    }
    if (m_matrix.size() <= M || m_matrix[0].size() <= N) {
      std::vector<std::vector<int>> a_matrix(M + 1, std::vector<int>(N + 1));
      m_matrix.swap(a_matrix);
    }
    for (IntegerType i = 1; i <= M; ++i) {
      m_matrix[i][0] = i;
    }
    for (IntegerType j = 1; j <= N; ++j) {
      m_matrix[0][j] = j;
    }
    for (IntegerType j = 1; j <= N; ++j) {
      for (IntegerType i = 1; i <= M; ++i) {
        m_matrix[i][j] =
            std::min({// Insertion
                      m_matrix[i][j - 1] + 1,
                      // Deletion
                      m_matrix[i - 1][j] + 1,
                      // Substitution
                      m_matrix[i - 1][j - 1] + (s[i - 1] == t[j - 1] ? 0 : 1)});
      }
    }
    return m_matrix[M][N];
  }
};

///
/// Damerau–Levenshtein metric
///
class DamerauLevenshteinDistance {
  mutable std::vector<std::vector<int>> m_matrix;

public:
  explicit DamerauLevenshteinDistance(
      size_t initial_size = BK_MATRIX_INITIAL_SIZE)
      : m_matrix(initial_size, std::vector<int>(initial_size)){};
  IntegerType operator()(const std::string &s, const std::string &t) const {
    const IntegerType M = s.size(), N = t.size();
    if (M == 0 || N == 0) {
      return N + M;
    }
    if (m_matrix.size() <= M || m_matrix[0].size() <= N) {
      std::vector<std::vector<int>> a_matrix(M + 1, std::vector<int>(N + 1));
      m_matrix.swap(a_matrix);
    }
    for (IntegerType i = 1; i <= M; ++i) {
      m_matrix[i][0] = i;
    }
    for (IntegerType j = 1; j <= N; ++j) {
      m_matrix[0][j] = j;
    }
    for (IntegerType j = 1; j <= N; ++j) {
      for (IntegerType i = 1; i <= M; ++i) {
        m_matrix[i][j] =
            std::min({// Insertion
                      m_matrix[i][j - 1] + 1,
                      // Deletion
                      m_matrix[i - 1][j] + 1,
                      // Substitution
                      m_matrix[i - 1][j - 1] + (s[i - 1] == t[j - 1] ? 0 : 1)});
        if (i > 1 && j > 1 && s[i] == t[j - 1] && s[i - 1] == t[j]) {
          // Transposition
          m_matrix[i][j] = std::min(m_matrix[i][j], m_matrix[i - 2][j - 2] + 1);
        }
      }
    }
    return m_matrix[M][N];
  }
};

}; // namespace metrics

template <typename Metric> class BKTree;
template <typename Metric> class BKTreeNode;
using ResultEntry = std::pair<std::string, int>;
using ResultList = std::vector<ResultEntry>;

///
/// Template class for BK-tree node
///
template <typename Metric> class BKTreeNode {
  friend class BKTree<Metric>;
  using MetricType = Metric;
  using NodeType = BKTreeNode<MetricType>;

  BKTreeNode(const std::string &value) : m_word(value) {}
  bool m_insert(const std::string &value, const MetricType &distance);
  bool m_erase(const std::string &value, const MetricType &distance);
  void m_find(ResultList &output, const std::string &value, const int &limit,
              const MetricType &metric) const;
  ResultList m_find_wrapper(const std::string &value, const int &limit,
                            const MetricType &metric) const;

  std::map<int, std::unique_ptr<NodeType>> m_children;
  std::string m_word;
};

///
/// Template class for BK-tree
///
template <typename Metric> class BKTree {
  using MetricType = Metric;
  using NodeType = typename BKTreeNode<MetricType>::NodeType;

public:
  BKTree(const MetricType &distance = Metric())
      : m_root(nullptr), m_metric(distance), m_tree_size(BK_TREE_INITIAL_SIZE) {
  }

  bool insert(const std::string &value);
  bool erase(const std::string &value);
  size_t size() const noexcept { return m_tree_size; }
  bool empty() const noexcept { return m_tree_size == 0; }
  [[nodiscard]] ResultList find(const std::string &value,
                                const int &limit) const;

private:
  std::unique_ptr<NodeType> m_root;
  const MetricType m_metric;
  size_t m_tree_size;
};

template <typename Metric>
bool BKTreeNode<Metric>::m_insert(const std::string &value,
                                  const MetricType &distance_metric) {
  const int distance_between = distance_metric(value, m_word);
  bool inserted = false;
  if (distance_between >= 0) {
    auto it = m_children.find(distance_between);
    if (it == m_children.end()) {
      m_children.emplace(std::make_pair(
          distance_between, std::unique_ptr<NodeType>(new NodeType(value))));
      inserted = true;
    } else {
      inserted = it->second->m_insert(value, distance_metric);
    }
  }
  return inserted;
}

template <typename Metric>
bool BKTreeNode<Metric>::m_erase(const std::string &value,
                                 const MetricType &distance_metric) {
  // Fixme: handle erasing root node
  const int distance_between = distance_metric(value, m_word);
  bool erased = false;
  if (distance_between > 0) {
    auto it = m_children.find(distance_between);
    if (it != m_children.end()) {
      if (it->second->m_word == value) {
        m_children.erase(it);
        erased = true;
      } else {
        erased = it->second->m_erase(value, distance_metric);
      }
    }
  }
  return erased;
}

template <typename Metric>
void BKTreeNode<Metric>::m_find(ResultList &output, const std::string &value,
                                const int &limit,
                                const MetricType &metric) const {
  const int distance = metric(value, m_word);
  if (distance <= limit) {
    output.push_back({m_word, distance});
  }
  for (auto iter = m_children.begin(); iter != m_children.end(); ++iter) {
    if (distance - limit <= iter->first and iter->first <= distance + limit) {
      iter->second->m_find(output, value, limit, metric);
    }
  }
}

template <typename Metric>
ResultList BKTreeNode<Metric>::m_find_wrapper(const std::string &value,
                                              const int &limit,
                                              const MetricType &metric) const {
  ResultList output;
  m_find(output, value, limit, metric);
  return output;
}

template <typename Metric>
bool BKTree<Metric>::insert(const std::string &value) {
  bool inserted = false;
  if (m_root == nullptr) {
    m_root = std::unique_ptr<NodeType>(new NodeType(value));
    m_tree_size = 1;
    inserted = true;
  } else if (m_root->m_insert(value, m_metric)) {
    ++m_tree_size;
    inserted = true;
  }
  return inserted;
}

template <typename Metric>
bool BKTree<Metric>::erase(const std::string &value) {
  bool erased = false;
  if (m_root == nullptr) {
    erased = true;
  } else if (m_root->m_erase(value, m_metric)) {
    --m_tree_size;
    erased = true;
  }
  return erased;
}

template <typename Metric>
ResultList BKTree<Metric>::find(const std::string &value,
                                const int &limit) const {
  if (!m_root) {
    return ResultList();
  }
  return m_root->m_find_wrapper(value, limit, m_metric);
}

}; // namespace bk_tree
