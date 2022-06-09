#include "../bktree/bktree.hpp"

#include <benchmark/benchmark.h>

#include <string_view>

constexpr static const std::string_view word = "word";

void TreeEditInsert(benchmark::State &state) {
  bk_tree::BKTree<bk_tree::metrics::EditDistance> tree_edit;
  for (auto _ : state) {
    benchmark::DoNotOptimize(tree_edit.insert(word));
  }
}

void TreeHammingInsert(benchmark::State &state) {
  bk_tree::BKTree<bk_tree::metrics::HammingDistance> tree_hamming;
  for (auto _ : state) {
    benchmark::DoNotOptimize(tree_hamming.insert(word));
  }
}

BENCHMARK(TreeEditInsert)->Unit(benchmark::kMicrosecond);
BENCHMARK(TreeHammingInsert)->Unit(benchmark::kMicrosecond);

int main(int argc, char **argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
  return 0;
}
