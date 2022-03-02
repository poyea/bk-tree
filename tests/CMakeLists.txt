include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SRC_FILES ./*.cpp)
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