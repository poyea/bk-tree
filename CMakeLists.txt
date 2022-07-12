# For BK tree build
cmake_minimum_required(VERSION 3.16..3.23)

project(bk-tree
    VERSION 0.1.1
    LANGUAGES CXX
    DESCRIPTION "Header-only Burkhard-Keller tree library"
    HOMEPAGE_URL "https://github.com/poyea/bk-tree")

if(MSVC)
    add_compile_options(/O2 /permissive- /W4)
else()
    add_compile_options(-O3 -Wall -Wextra -Wpedantic -fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

set(CMAKE_CXX_STANDARD 20)

include_directories(
    ${PROJECT_SOURCE_DIR}/bktree
)

file(GLOB EXAMPLE_SRC_FILES ${PROJECT_SOURCE_DIR}/examples/*.cpp)
foreach(file ${EXAMPLE_SRC_FILES})
    file(GLOB FILE_SRC
        "${PROJECT_SOURCE_DIR}/bktree/*.hpp"
        ${file}
        )
    get_filename_component(FILE_NAME ${file} NAME_WLE)
    add_executable(${FILE_NAME} ${FILE_SRC})
endforeach()

# For BK tree test build
if(TESTS)
    enable_testing()
    message("-- Building Tests")
    add_subdirectory(tests)
endif()

# For BK tree benchmark build
if(BENCHMARKS)
    message("-- Building Benchmarks")
    add_subdirectory(benchmarks)
endif()

# For BK tree documentation build
find_package(Doxygen)

option(DOCS "Create and install API documentation with Doxygen" ${DOXYGEN_FOUND})

if(DOCS)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation")
    endif()

    set(DOXYGEN_EXCLUDE_SYMBOLS "BKTreeNode")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/docs/README.md")
    set(DOXYGEN_USE_MATHJAX YES)
    set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)

    doxygen_add_docs(Documentation
        ${PROJECT_SOURCE_DIR}/bktree
        ${PROJECT_SOURCE_DIR}/docs
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bktree
        COMMENT "Generating API documentation with Doxygen"
    )

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION documentation)
endif()
