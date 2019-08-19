project(tsl_type_traits C CXX)
enable_language(CXX)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++17")

#include_directories(/home/athomps/libs/include)

add_library(tsl_type_traits STATIC
   type_traits.cpp
)

add_subdirectory(ut)
