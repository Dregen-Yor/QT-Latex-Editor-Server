cmake_minimum_required(VERSION 3.29)
project(QT-Latex-Editor-Server VERSION 0.1 LANGUAGES CXX)
find_package(Boost 1.71.0 REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++20")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(proxygen REQUIRED)
# find_package(proxygen REQUIRED)
# find_package(folly REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-tree-slp-vectorize")

include_directories(include)

add_subdirectory(src)