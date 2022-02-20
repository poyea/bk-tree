# For BK tree build
cmake_minimum_required(VERSION 3.12..3.16)

project(bk-tree VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)

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
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)

    enable_testing()
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
