cmake_minimum_required(VERSION 3.5)

project(tesseract_example LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(/usr/include/tesseract/)
include_directories(/usr/include/leptonica/)

add_executable(tesseract_example
  main.cpp
  utils.cpp
)

target_link_libraries(tesseract_example PRIVATE tesseract lept)