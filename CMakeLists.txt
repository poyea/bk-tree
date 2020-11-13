# For BK tree build
cmake_minimum_required(VERSION 3.1.0)
set (CMAKE_CXX_STANDARD 14)
project(bk-tree)
include_directories(bktree)
add_executable(bk_tree
  examples/example.cpp
  bktree/bktree.hpp
)
