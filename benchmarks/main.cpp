#include "../bktree/bktree.hpp"

#include <benchmark/benchmark.h>

void TreeInsert(benchmark::State &state) {
  bk_tree::BKTree<bk_tree::metrics::EditDistance> tree;
  bk_tree::ResultList results;
  for (auto _ : state) {
    benchmark::DoNotOptimize(tree.insert("word"));
  }
}

BENCHMARK(TreeInsert)->Unit(benchmark::kMicrosecond);

int main(int argc, char **argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
  return 0;
}