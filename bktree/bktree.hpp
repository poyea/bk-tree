#ifndef BK_TREE_H
#define BK_TREE_H

#define BK_ED_MATRIX_INITIAL_SIZE 1
#define BK_TREE_INITIAL_SIZE 0
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace bk_tree {
typedef u_int32_t ui;
namespace metrics {

///
/// Hamming distance metric
///
class hamming_distance {
public:
  explicit hamming_distance() = default;
  ui operator()(const std::string &s, const std::string &t) const {
    const ui m = s.size();
    const ui n = t.size();
    if (m != n) {
      return std::numeric_limits<ui>::max();
    }
    const ui m_comparsion_size = std::min(m, n);
    ui counter = 0;
    for (ui i = 0; i < m_comparsion_size; ++i) {
      counter += (s[i] != t[i]);
    }
    return counter;
  }
};

///
/// Edit distance metric
///
class edit_distance {
  mutable std::vector<std::vector<int>> m_matrix;

public:
  explicit edit_distance(size_t initial_size = BK_ED_MATRIX_INITIAL_SIZE)
      : m_matrix(initial_size, std::vector<int>(initial_size)){};
  ui operator()(const std::string &s, const std::string &t) const {
    const ui m = s.size();
    const ui n = t.size();
    if (m == 0 or n == 0) {
      return n + m;
    }
    if (m_matrix.size() <= m or m_matrix[0].size() <= n) {
      std::vector<std::vector<int>> a_matrix(m + 1, std::vector<int>(n + 1));
      m_matrix.swap(a_matrix);
    }
    for (ui i = 1; i <= m; ++i) {
      m_matrix[i][0] = i;
    }
    for (ui j = 1; j <= n; ++j) {
      m_matrix[0][j] = j;
    }
    for (ui j = 1; j <= n; ++j) {
      for (ui i = 1; i <= m; ++i) {
        m_matrix[i][j] = std::min({
            m_matrix[i][j - 1] + 1, // Insertion
            m_matrix[i - 1][j] + 1, // Deletion
            m_matrix[i - 1][j - 1] +
                (s[i - 1] == t[j - 1] ? 0 : 1) // Substitution
        });
      }
    }
    return m_matrix[m][n];
  }
};
}; // namespace metrics

template <typename Metric> class bk_tree;
template <typename Metric> class tree_node;
typedef std::pair<std::string, int> psi;
typedef std::vector<psi> vecpair;

///
/// Template class for BK-tree node
///
template <typename Metric> class tree_node {
  friend class bk_tree<Metric>;
  typedef Metric metric_type;
  typedef tree_node<metric_type> node_type;

  mutable std::map<int, std::unique_ptr<node_type>> m_children;
  std::string m_word;

  tree_node(const std::string &value) : m_word(value) {}
  bool insert(const std::string &value, const metric_type &distance) const;
  vecpair m_find_wrapper(const std::string &value, const int &limit,
                         const metric_type &metric) const;
  void find(vecpair &output, const std::string &value, const int &limit,
            const metric_type &metric) const;
};

///
/// Template class for BK-tree
///
template <typename Metric> class bk_tree {
  typedef Metric metric_type;
  typedef typename tree_node<metric_type>::node_type node_type;

  const metric_type m_metric;
  std::unique_ptr<node_type> m_root;
  size_t m_tree_size;

public:
  bool insert(const std::string &value);
  vecpair find(const std::string &value, const int &limit) const;
  inline size_t size() const;
  bk_tree(const metric_type &distance = Metric())
      : m_root(nullptr), m_metric(distance), m_tree_size(BK_TREE_INITIAL_SIZE) {
  }
};

template <typename Metric>
bool tree_node<Metric>::insert(const std::string &value,
                               const metric_type &distance_metric) const {
  const int distance_between = distance_metric(value, this->m_word);
  bool inserted = false;
  if (distance_between > 0) {
    auto it = m_children.find(distance_between);
    if (it == m_children.end()) {
      m_children.emplace(std::make_pair(
          distance_between, std::unique_ptr<node_type>(new node_type(value))));
      inserted = true;
    } else {
      inserted = it->second->insert(value, distance_metric);
    }
  }
  return inserted;
}

template <typename Metric>
vecpair tree_node<Metric>::m_find_wrapper(const std::string &value,
                                          const int &limit,
                                          const metric_type &metric) const {
  vecpair output;
  this->find(output, value, limit, metric);
  return output;
}

template <typename Metric>
void tree_node<Metric>::find(vecpair &output, const std::string &value,
                             const int &limit,
                             const metric_type &metric) const {
  const int distance = metric(value, this->m_word);
  if (distance <= limit) {
    output.push_back({this->m_word, distance});
  }
  for (auto iter = m_children.begin(); iter != m_children.end(); ++iter) {
    if (distance - limit <= iter->first and iter->first <= distance + limit) {
      iter->second->find(output, value, limit, metric);
    }
  }
}

template <typename Metric>
bool bk_tree<Metric>::insert(const std::string &value) {
  bool inserted = false;
  if (m_root == nullptr) {
    m_root = std::unique_ptr<node_type>(new node_type(value));
    m_tree_size = 1;
    inserted = true;
  } else if (m_root->insert(value, m_metric)) {
    ++m_tree_size;
    inserted = true;
  }
  return inserted;
}

template <typename Metric>
vecpair bk_tree<Metric>::find(const std::string &value,
                              const int &limit) const {
  return m_root->m_find_wrapper(value, limit, m_metric);
}

template <typename Metric> inline size_t bk_tree<Metric>::size() const {
  return m_tree_size;
}

}; // namespace bk_tree

#endif // BK_TREE_H
