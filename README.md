
<img align="left" width="150" height="150" src="https://user-images.githubusercontent.com/24757020/150530071-e3792d5e-700b-4e50-84fe-9948b3afe8fa.png" alt="Palm Tree">

# bk-tree ![CMake](https://github.com/poyea/bk-tree/workflows/CMake/badge.svg)

Header-only Burkhard-Keller tree implementation in C++, with minimal examples.

<br/>

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

## License
MIT

## References

Fred J. Damerau. 1964. A technique for computer detection and correction of spelling errors. Communications of the ACM 7, 3 (1964), 171–176. DOI:http://dx.doi.org/10.1145/363958.363994 

Vladimir I. Levenshtein. 1966. Binary codes capable of correcting deletions, insertions, and reversals. Soviet physics doklady 10, 8 (1966), 845-848.

W.A. Burkhard and R.M. Keller. 1973. Some approaches to best-match file searching. Communications of the ACM 16, 4 (1973), 230–236. DOI:http://dx.doi.org/10.1145/362003.362025 
