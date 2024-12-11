cmake_minimum_required(VERSION 3.22)
project(bfs)

set(CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -Werror")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_library(bfs_lib src/bfs.cpp)

add_executable(test_correct src/test/utils.cpp src/test/test_correct.cpp)

add_executable(test_time src/test/utils.cpp src/test/test_time.cpp)

target_link_libraries(test_correct bfs_lib)

target_link_libraries(test_time bfs_lib)

add_subdirectory(parlaylib)

target_link_libraries(bfs_lib parlay)

target_include_directories(bfs_lib PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/parlaylib/include")


target_include_directories(test_correct PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/parlaylib/include")

target_include_directories(test_time PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/parlaylib/include")
