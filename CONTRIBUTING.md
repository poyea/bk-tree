# Contribution Guidelines

We are under development! Feel free to make our Contribution Guidelines better!

Use CMake 3.25 or newer and a compiler with C++26 support. Use a fresh build
directory when changing compilers; CMake caches the compiler selection.

## Building the examples
```bash
$ cmake -S . -B build-examples -DCMAKE_CXX_COMPILER=clang++
$ cmake --build build-examples --parallel
```

## Building the tests
```bash
$ cmake -S . -B build-tests -DCMAKE_CXX_COMPILER=clang++ -DTESTS=ON
$ cmake --build build-tests --parallel
$ ctest --test-dir build-tests --output-on-failure
```

## Building the benchmarks
```bash
$ cmake -S . -B build-benchmarks -DCMAKE_CXX_COMPILER=clang++ -DBENCHMARKS=ON
$ cmake --build build-benchmarks --parallel
```

## Building the documentation
```bash
$ cmake -S . -B build-docs -DCMAKE_CXX_COMPILER=clang++ -DDOCS=ON
$ cmake --build build-docs --target Documentation
```
