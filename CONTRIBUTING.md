# Contribution Guidelines

We are under development! Feel free to make our Contribution Guidelines better!

## Building the examples
```bash
$ cmake --version 
cmake version 3.16.3
$ mkdir build && cd build
$ CXX=clang++ cmake ..
$ make -sj
```

## Building the tests
```bash
$ mkdir build && cd build
$ CXX=clang++ cmake .. -DTESTS=ON
$ make -sj
$ make test
```

## Building the benchmarks
```bash
$ mkdir build && cd build
$ CXX=clang++ cmake .. -DBENCHMARKS=ON
$ make -sj
```

## Building the documentation
```bash
$ mkdir build && cd build
$ CXX=clang++ cmake .. -DDOCS=ON
$ doxygen Doxyfile.Documentation
```
