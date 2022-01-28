# For BK tree build
cmake_minimum_required(VERSION 3.1.0)

set (CMAKE_CXX_STANDARD 20)

project(bk-tree)

include_directories(
    ${PROJECT_SOURCE_DIR}/bktree
    ${PROJECT_SOURCE_DIR}/example
)

file(GLOB ALL_SRC
        "${PROJECT_SOURCE_DIR}/bktree/*.hpp"
        "${PROJECT_SOURCE_DIR}/examples/*.cpp"
        )

add_library(bk_tree_src ${ALL_SRC})

add_executable(bk_tree_examples ${ALL_SRC})

# For BK tree test build
# See README.md for details
if(TESTS)
    enable_testing()
    add_subdirectory(googletest)
    file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
    foreach(file ${TEST_SRC_FILES})
        get_filename_component(FILE_NAME ${file} NAME_WLE)
        add_executable(test_${FILE_NAME} ${file})
        target_link_libraries(test_${FILE_NAME} gtest gtest_main)        
        add_test(
            NAME BKTree_TEST_${FILE_NAME}
            COMMAND test_${FILE_NAME}
        )
        add_custom_command(
            TARGET test_${FILE_NAME}
            COMMENT "Running the test ${FILE_NAME}"
            POST_BUILD
            COMMAND test_${FILE_NAME}
        )
    endforeach()
endif()
