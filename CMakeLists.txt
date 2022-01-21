# For BK tree build
cmake_minimum_required(VERSION 3.1.0)

set (CMAKE_CXX_STANDARD 20)

project(bk-tree)

include_directories(
    ${PROJECT_SOURCE_DIR}/bktree
    ${PROJECT_SOURCE_DIR}/example
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/bktree/*.hpp"
        "${PROJECT_SOURCE_DIR}/examples/*.cpp"
        )

add_executable(bk_tree ${all_SRCS})
