# Contribution Guidelines

We are under development! Feel free to make our Contribution Guidelines better!

## Building the examples
```bash
$ cmake --version 
cmake version 3.16.3
$ mkdir build
$ cd build
$ CXX=clang++ cmake ..
$ make
```

## Building the tests
```bash
$ cd build
$ CXX=clang++ cmake .. -DTESTS=ON
$ make
$ make test
```