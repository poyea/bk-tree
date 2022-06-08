include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)

FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG        v1.6.1
)

FetchContent_MakeAvailable(googletest googlebenchmark)

add_executable(main main.cpp)
target_link_libraries(main benchmark::benchmark)
