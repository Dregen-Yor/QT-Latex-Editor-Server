cmake_minimum_required(VERSION 3.29)
project(QT-Latex-Editor-Server VERSION 0.1 LANGUAGES CXX)
find_package(Boost 1.71.0 REQUIRED)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  "/usr/local/lib/cmake/proxygen"
  )
list(APPEND CMAKE_PREFIX_PATH "/opt/glog")
find_package(proxygen REQUIRED)
find_package(gflags REQUIRED)  # From the common CMake/
find_package(glog REQUIRED)  # From the common CMake/
message(STATUS "proxygen lib path: ${proxygen_INCLUDE_DIRECTORIES}")

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()


add_subdirectory(src)