//
// bk-tree   Header-only Burkhard-Keller tree library
// Copyright (C) 2020-2023  John Law
//
// This file is part of bk-tree.
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
#ifndef BK_LEE_ALPHABET_SIZE
#define BK_LEE_ALPHABET_SIZE 26
#endif
#ifndef BK_TREE_INITIAL_SIZE
#define BK_TREE_INITIAL_SIZE 0
#endif
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief BK-tree namespace
 */
namespace bk_tree {

using integer_type = std::uint64_t;

/**
 * @brief Metrics namespace
 */
namespace metrics {

/**
 * @brief Metric interface for string distances
 */
template <typename Metric>
class Distance {
public:
  integer_type operator()(std::string_view s, std::string_view t) const {
    return (static_cast<Metric const *>(this))->compute_distance(s, t);
  }
};

/**
 * @brief Length metric
 *
 * \f$d(x, y) = |m - n|\f$ where
 * \f$m\f$ is the length of \f$x\f$, and \f$n\f$ is the length of \f$y\f$, for any \f$x,
 * y.\f$
 */
class LengthDistance final : public Distance<LengthDistance> {
public:
  explicit LengthDistance(){};
  integer_type compute_distance(std::string_view s, std::string_view t) const noexcept {
    return s.length() > t.length() ? s.length() - t.length() : t.length() - s.length();
  }
};

/**
 * @brief Identity metric
 *
 * \f$d(x, y) = 1\f$ for any \f$x, y.\f$
 */
class IdentityDistance final : public Distance<IdentityDistance> {
public:
  explicit IdentityDistance(){};
  integer_type compute_distance(std::string_view, std::string_view) const noexcept {
    return integer_type{1};
  }
};

/**
 * @brief Lee distance metric
 *
 * \f[d(x, y) = \sum_{i=0}^{n-1} \min\{|x_i - y_i|, m - |x_i - y_i|\},\f]
 * where \f$m\f$ is the alphabet size, and \f$x\f$ and \f$y\f$ are of the same length.
 * When \f$m = 2\f$ or \f$m = 3\f$, LeeDistance is the same as HammingDistance.
 */
class LeeDistance final : public Distance<LeeDistance> {
  integer_type m_alphabet_size;

public:
  explicit LeeDistance(integer_type alphabet_size = BK_LEE_ALPHABET_SIZE)
      : m_alphabet_size(alphabet_size){};
  integer_type compute_distance(std::string_view s, std::string_view t) const noexcept {
    const integer_type M = s.length(), N = t.length();
    if (M != N) {
      return std::numeric_limits<integer_type>::max();
    }
    const integer_type m_comparison_size = M;
    integer_type counter = 0, diff;
    for (integer_type i = 0; i < m_comparison_size; ++i) {
      diff = std::abs(s[i] - t[i]);
      counter += std::min(diff, m_alphabet_size - diff);
    }
    return counter;
  }
};

/**
 * @brief Longest Common Subsequence distance metric
 *
 * \f$d(x_m, y_n),\f$ where
 * \f$m\f$ is the length of \f$x\f$, \f$n\f$ is the length of \f$y\f$.
 * \f[\begin{equation}
 * d(x_i, y_j)=
 *   \begin{cases}
 *     0, & \text{if } i = 0 \text{ or } j = 0 \\
 *     d(x_{i-1}, y_{j-1}) + 1, & \text{if } x_i = y_j \\
 *     \max\{d(x_{i-1}, y_j), d(x_i, y_{j-1})\}, & \text{if } x_i \neq y_j
 *   \end{cases}
 * \end{equation}\f]
 * for any \f$0\le i < m\f$ and \f$0\le j < n.\f$
 */
class LCSubseqDistance final : public Distance<LCSubseqDistance> {
  mutable std::vector<integer_type> m_current, m_previous;

public:
  explicit LCSubseqDistance(size_t initial_size = BK_LCS_MATRIX_INITIAL_SIZE)
      : m_current(initial_size), m_previous(initial_size){};
  integer_type compute_distance(std::string_view s, std::string_view t) const noexcept {
    const integer_type M = s.length(), N = t.length();
    if (M == 0 || N == 0) {
      return 0;
    }
    if (m_current.size() <= N || m_previous.size() <= N) {
      m_current.resize(N + 1);
      m_previous.resize(N + 1);
    }
    std::fill(m_previous.begin(), m_previous.end(), 0);
    for (integer_type i = 1; i <= M; ++i) {
      for (integer_type j = 1; j <= N; ++j) {
        if (s[i - 1] == t[j - 1]) {
          m_current[j] = m_previous[j - 1] + 1;
        } else {
          m_current[j] = std::max(m_previous[j], m_current[j - 1]);
        }
      }
      m_previous = m_current;
    }
    return m_previous[N];
  }
};

/**
 * @brief Hamming distance metric
 *
 * \f$d(x, y) = \displaystyle\sum_{i=0}^{n-1} x_i \bigoplus y_i,\f$
 * where \f$\bigoplus\f$ is the XOR operator, and \f$x\f$ and \f$y\f$
 * are of the same length.
 */
class HammingDistance final : public Distance<HammingDistance> {
public:
  explicit HammingDistance() = default;
  integer_type compute_distance(std::string_view s, std::string_view t) const noexcept {
    const integer_type M = s.length(), N = t.length();
    if (M != N) {
      return std::numeric_limits<integer_type>::max();
    }
    const integer_type m_comparison_size = M;
    integer_type counter = 0;
    for (integer_type i = 0; i < m_comparison_size; ++i) {
      counter += (s[i] != t[i]);
    }
    return counter;
  }
};

/**
 * @brief Edit distance metric
 *
 * Related to DamerauLevenshteinDistance.
 *
 * \f$d(x_m, y_n),\f$ where
 * \f$m\f$ is the length of \f$x\f$, \f$n\f$ is the length of \f$y\f$,
 * \f[\begin{equation}
 * d(x_i, y_j)=
 *   \begin{cases}
 *     i, & \text{if } j = 0 \\
 *     j, & \text{if } i = 0 \\
 *       \min\left\{
 *           d(x_i, y_{j-1}) + 1,
 *           d(x_{i-1}, y_j) + 1,
 *     \begin{cases}
 *           d(x_{i-1}, y_{j-1}) + 1, & x_i \neq y_j \\
 *           d(x_{i-1}, y_{j-1}), & \text{otherwise}
 *     \end{cases}
 *     \right\}
 *   \end{cases}
 * \end{equation}\f]
 * for any \f$0\le i < m\f$ and \f$0\le j < n.\f$
 */
class EditDistance final : public Distance<EditDistance> {
  mutable std::vector<std::vector<integer_type>> m_matrix;

public:
  explicit EditDistance(size_t initial_size = BK_ED_MATRIX_INITIAL_SIZE)
      : m_matrix(initial_size, std::vector<integer_type>(initial_size)){};
  integer_type compute_distance(std::string_view s, std::string_view t) const noexcept {
    const integer_type M = s.length(), N = t.length();
    if (M == 0 || N == 0) {
      return N + M;
    }
    if (m_matrix.size() <= M || m_matrix[0].size() <= N) {
      std::vector<std::vector<integer_type>> a_matrix(M + 1,
                                                      std::vector<integer_type>(N + 1));
      m_matrix.swap(a_matrix);
    }
    for (integer_type i = 1; i <= M; ++i) {
      m_matrix[i][0] = i;
    }
    for (integer_type j = 1; j <= N; ++j) {
      m_matrix[0][j] = j;
    }
    for (integer_type j = 1; j <= N; ++j) {
      for (integer_type i = 1; i <= M; ++i) {
        m_matrix[i][j] = std::min(
            {m_matrix[i][j - 1] + 1 /*Insertion*/, m_matrix[i - 1][j] + 1 /*Deletion*/,
             m_matrix[i - 1][j - 1] + (s[i - 1] != t[j - 1]) /*Substitution*/});
      }
    }
    return m_matrix[M][N];
  }
};

/**
 * @brief Damerau–Levenshtein metric
 *
 * Similar to EditDistance, but with transposition.
 */
class DamerauLevenshteinDistance final : public Distance<DamerauLevenshteinDistance> {
  mutable std::vector<std::vector<integer_type>> m_matrix;

public:
  explicit DamerauLevenshteinDistance(size_t initial_size = BK_MATRIX_INITIAL_SIZE)
      : m_matrix(initial_size, std::vector<integer_type>(initial_size)){};
  integer_type compute_distance(std::string_view s, std::string_view t) const noexcept {
    const integer_type M = s.length(), N = t.length();
    if (M == 0 || N == 0) {
      return N + M;
    }
    if (m_matrix.size() <= M || m_matrix[0].size() <= N) {
      std::vector<std::vector<integer_type>> a_matrix(M + 1,
                                                      std::vector<integer_type>(N + 1));
      m_matrix.swap(a_matrix);
    }
    for (integer_type i = 1; i <= M; ++i) {
      m_matrix[i][0] = i;
    }
    for (integer_type j = 1; j <= N; ++j) {
      m_matrix[0][j] = j;
    }
    for (integer_type j = 1; j <= N; ++j) {
      for (integer_type i = 1; i <= M; ++i) {
        m_matrix[i][j] = std::min(
            {m_matrix[i][j - 1] + 1 /*Insertion*/, m_matrix[i - 1][j] + 1 /*Deletion*/,
             m_matrix[i - 1][j - 1] + (s[i - 1] == t[j - 1] ? 0 : 1) /*Substitution*/});
        if (i > 1 && j > 1 && s[i - 1] == t[j - 2] && s[i - 2] == t[j - 1]) {
          m_matrix[i][j] =
              std::min(m_matrix[i][j], m_matrix[i - 2][j - 2] + 1 /*Transposition*/);
        }
      }
    }
    return m_matrix[M][N];
  }
};

} // namespace metrics

namespace helpers {
std::false_type is_metric_impl(...);

template <typename Metric>
std::true_type is_metric_impl(const volatile metrics::Distance<Metric> &);

template <typename Metric>
using is_metric = decltype(is_metric_impl(std::declval<Metric &>()));
} // namespace helpers

template <typename Metric>
class BKTree;
template <typename Metric>
class BKTreeNode;

using ResultEntry = std::pair<std::string, int>;
using ResultList = std::vector<ResultEntry>;

template <typename Metric>
class BKTreeNode {
  friend class BKTree<Metric>;
  using metric_type = Metric;
  using node_type = BKTreeNode<metric_type>;

  BKTreeNode(std::string_view value) : m_word(value) {}
  bool _insert(std::string_view value, const metric_type &distance);
  bool _erase(std::string_view value, const metric_type &distance);
  void _find(ResultList &output, std::string_view value, int limit,
             const metric_type &metric) const;
  ResultList _find_wrapper(std::string_view value, int limit,
                           const metric_type &metric) const;

  std::map<int, std::unique_ptr<node_type>> m_children;
  std::string m_word;

  friend std::ostream &operator<<(std::ostream &oss, const BKTreeNode &node) {
    oss << node.m_word;
    return oss;
  }

public:
  std::string_view word() const noexcept { return m_word; }
};

/**
 * @brief BK-tree template class
 */
template <typename Metric>
class BKTree {
  static_assert(helpers::is_metric<Metric>::value, "Metric must be of type Distance");

  using metric_type = Metric;
  using node_type = typename BKTreeNode<metric_type>::node_type;

public:
  /**
   * @brief BK-tree class iterator
   */
  class Iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::unique_ptr<node_type>;
    using pointer = std::unique_ptr<node_type> *;
    using reference = std::unique_ptr<node_type> &;

  public:
    Iterator() = default;
    Iterator(pointer ptr) : m_pointer(ptr) {}

    pointer operator->() { return m_pointer; }

    reference operator*() const { return *m_pointer; }

    Iterator &operator++() {
      if (m_pointer == nullptr) {
        throw std::out_of_range("No more tree node");
      }
      for (auto &[_, child] : (*m_pointer)->m_children) {
        m_queue.push(&child);
      }
      if (m_queue.empty()) {
        m_pointer = nullptr;
      } else {
        m_pointer = m_queue.front();
        m_queue.pop();
      }
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp{*this};
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.m_pointer == b.m_pointer;
    };

    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.m_pointer != b.m_pointer;
    };

  private:
    pointer m_pointer;
    std::queue<pointer> m_queue;
  };

public:
  BKTree(const metric_type &distance = Metric())
      : m_root(nullptr), m_metric(distance), m_tree_size(BK_TREE_INITIAL_SIZE) {}

  BKTree(std::initializer_list<std::string_view> list)
      : m_root(nullptr), m_metric(Metric()), m_tree_size(BK_TREE_INITIAL_SIZE) {
    for (auto &str : list) {
      insert(str);
    }
  }

  BKTree(const BKTree &other) : BKTree(other.m_metric) {
    if (other.m_root == nullptr) {
      return;
    }
    std::queue<std::unique_ptr<node_type> const *> bq;
    bq.push(&(other.m_root));
    while (!bq.empty()) {
      auto *nptr = bq.front();
      bq.pop();
      this->insert((*nptr)->m_word);
      for (auto &[_, child_node] : (*nptr)->m_children) {
        bq.push(&child_node);
      }
    }
  }

  BKTree(BKTree &&other) noexcept
      : m_root(std::exchange(other.m_root, nullptr)), m_tree_size(other.m_tree_size) {}

  BKTree &operator=(const BKTree &other) {
    if (this == &other) {
      return *this;
    }
    BKTree temp(other);
    std::swap(m_root, temp.m_root);
    std::swap(m_tree_size, temp.m_tree_size);
    return *this;
  }

  BKTree &operator=(BKTree &&other) noexcept {
    std::swap(m_root, other.m_root);
    std::swap(m_tree_size, other.m_tree_size);
    return *this;
  }

  ~BKTree() = default;

  bool insert(std::string_view value);
  bool erase(std::string_view value);
  size_t size() const noexcept { return m_tree_size; }
  bool empty() const noexcept { return m_tree_size == 0; }
  [[nodiscard]] ResultList find(std::string_view value, int limit) const;

  Iterator begin() { return Iterator(&m_root); }
  Iterator end() { return Iterator(); }

private:
  std::unique_ptr<node_type> m_root;
  const metric_type m_metric;
  size_t m_tree_size;
};

template <typename Metric>
bool BKTreeNode<Metric>::_insert(std::string_view value,
                                 const metric_type &distance_metric) {
  const int distance_between = distance_metric(value, m_word);
  bool inserted = false;
  if (distance_between >= 0) {
    auto it = m_children.find(distance_between);
    if (it == m_children.end()) {
      m_children.emplace(std::make_pair(
          distance_between, std::unique_ptr<node_type>(new node_type(value))));
      inserted = true;
    } else {
      inserted = it->second->_insert(value, distance_metric);
    }
  }
  return inserted;
}

template <typename Metric>
bool BKTreeNode<Metric>::_erase(std::string_view value,
                                const metric_type &distance_metric) {
  bool erased = false;
  const int distance_between = distance_metric(value, m_word);
  auto it = m_children.find(distance_between);
  if (it != m_children.end()) {
    if (it->second->m_word == value) {
      auto node = std::move(it->second);
      m_children.erase(it);
      std::queue<std::unique_ptr<node_type> const *> bq;
      for (auto const &[_, child_node] : node->m_children) {
        bq.push(&child_node);
      }
      while (!bq.empty()) {
        auto *node = bq.front();
        bq.pop();
        for (auto const &[_, child_node] : (*node)->m_children) {
          bq.push(&child_node);
        }
        _insert((*node)->m_word, distance_metric);
      }
      erased = true;
    } else {
      erased = it->second->_erase(value, distance_metric);
    }
  } else {
    for (auto const &[_, child] : m_children) {
      if (child->_erase(value, distance_metric)) {
        return true;
      }
    }
  }
  return erased;
}

template <typename Metric>
void BKTreeNode<Metric>::_find(ResultList &output, std::string_view value,
                               int limit, const metric_type &metric) const {
  const int distance = metric(value, m_word);
  if (distance <= limit) {
    output.push_back({m_word, distance});
  }
  for (auto const &[dist, node] : m_children) {
    if (std::abs(dist - distance) <= limit) {
      node->_find(output, value, limit, metric);
    }
  }
}

template <typename Metric>
ResultList BKTreeNode<Metric>::_find_wrapper(std::string_view value, int limit,
                                             const metric_type &metric) const {
  ResultList output;
  _find(output, value, limit, metric);
  return output;
}

template <typename Metric>
bool BKTree<Metric>::insert(std::string_view value) {
  bool inserted = false;
  if (m_root == nullptr) {
    m_root = std::unique_ptr<node_type>(new node_type(value));
    ++m_tree_size;
    inserted = true;
  } else if (m_root->_insert(value, m_metric)) {
    ++m_tree_size;
    inserted = true;
  }
  return inserted;
}

template <typename Metric>
bool BKTree<Metric>::erase(std::string_view value) {
  bool erased = false;
  if (m_root == nullptr) {
    erased = false;
  } else if (m_root->m_word == value) {
    if (m_tree_size > 1) {
      auto &replacement_node = m_root->m_children.begin()->second;
      std::queue<std::unique_ptr<node_type> const *> bq;
      for (bool first = true; auto const &[_, node] : m_root->m_children) {
        if (first) {
          first = false;
          continue;
        }
        bq.push(&node);
      }
      while (!bq.empty()) {
        auto node = bq.front();
        bq.pop();
        for (auto const &[_, child] : (*node)->m_children) {
          bq.push(&child);
        }
        replacement_node->_insert((*node)->m_word, m_metric);
      }
      m_root = std::move(replacement_node);
    } else {
      m_root.reset(nullptr);
    }
    --m_tree_size;
    erased = true;
  } else if (m_root->_erase(value, m_metric)) {
    --m_tree_size;
    erased = true;
  }
  return erased;
}

template <typename Metric>
ResultList BKTree<Metric>::find(std::string_view value, int limit) const {
  if (m_root == nullptr) {
    return ResultList{};
  }
  return m_root->_find_wrapper(value, limit, m_metric);
}

} // namespace bk_tree
