# Contribution Guidelines

We are under development! Feel free to make our Contribution Guidelines better!

## Building the examples
```bash
$ cmake --version 
cmake version 3.16.3
$ CXX=clang++ cmake -B build
$ cmake --build build -j
```

## Building the tests
```bash
$ CXX=clang++ cmake -B build -DTESTS=ON
$ cmake --build build -j
$ ctest --test-dir build
```

## Building the benchmarks
```bash
$ CXX=clang++ cmake -B build -DBENCHMARKS=ON
$ cmake --build build -j
```

## Building the documentation
```bash
$ CXX=clang++ cmake -B build -DDOCS=ON
$ doxygen build/Doxyfile.Documentation
```
