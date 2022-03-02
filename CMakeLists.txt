# For BK tree build
cmake_minimum_required(VERSION 3.12..3.16)

project(bk-tree
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "Header-only Burkhard-Keller tree library"
    HOMEPAGE_URL "https://github.com/poyea/bk-tree")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(ENABLE_DEVELOPER_MODE TRUE CACHE BOOL "Enable 'developer mode'")

include_directories(
    ${PROJECT_SOURCE_DIR}/bktree
    ${PROJECT_SOURCE_DIR}/example
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
# See README.md for details
if(TESTS)
    enable_testing()
    message("-- Building Tests")
    add_subdirectory(tests)
endif()
