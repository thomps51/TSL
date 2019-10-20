project(tsl_meta_ut)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++17")

include_directories(/home/athomps/libs/include)

add_executable(tsl_meta_ut
    main.cpp
    filter_parameter_pack_ut.cpp
    map_ut.cpp
)
