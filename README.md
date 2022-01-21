# <p align="center">bk-tree</p>
<p align="center">Header-only Burkhard-Keller tree implementation in C++</p>

![CMake](https://github.com/poyea/bk-tree/workflows/CMake/badge.svg)

## Building the example
```bash
$ cmake --version 
cmake version 3.16.3
$ CXX=clang++ cmake . -B build
$ cd build
$ make
```

## License
MIT

## References

Fred J. Damerau. 1964. A technique for computer detection and correction of spelling errors. Communications of the ACM 7, 3 (1964), 171–176. DOI:http://dx.doi.org/10.1145/363958.363994 

Vladimir I. Levenshtein. 1966. Binary codes capable of correcting deletions, insertions, and reversals. Soviet physics doklady 10, 8 (1966), 845-848.

W.A. Burkhard and R.M. Keller. 1973. Some approaches to best-match file searching. Communications of the ACM 16, 4 (1973), 230–236. DOI:http://dx.doi.org/10.1145/362003.362025 
