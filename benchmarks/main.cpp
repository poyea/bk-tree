#include "../bktree/bktree.hpp"

#include <benchmark/benchmark.h>

#include <string_view>

constexpr static const std::string_view word = "word";

#define BKTREE_BENCHMARK_CASE(F, N)                                                    \
  void Bench_##F(benchmark::State &state) {                                            \
    bk_tree::BKTree<bk_tree::metrics::N> tree;                                         \
    for (auto _ : state) {                                                             \
      benchmark::DoNotOptimize(tree.insert(word));                                     \
    }                                                                                  \
  }                                                                                    \
  BENCHMARK(Bench_##F)->Iterations(1000)->Unit(benchmark::kMicrosecond);

BKTREE_BENCHMARK_CASE(TreeUniformInsert, UniformDistance)
BKTREE_BENCHMARK_CASE(TreeHammingInsert, HammingDistance)
BKTREE_BENCHMARK_CASE(TreeLeeInsert, LeeDistance)
BKTREE_BENCHMARK_CASE(TreeLCSubseqInsert, LCSubseqDistance)
BKTREE_BENCHMARK_CASE(TreeEditInsert, EditDistance)
BKTREE_BENCHMARK_CASE(TreeDamerauLevenshteinInsert, DamerauLevenshteinDistance)

int main(int argc, char **argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
  return 0;
}
