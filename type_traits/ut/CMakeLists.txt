project(tsl_type_traits_ut)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++17")

include_directories(/home/athomps/libs/include)

add_executable(tsl_type_traits_ut
    main.cpp
    add_array_ut.cpp
    array_size_ut.cpp
    conditional_ut.cpp
    enable_if_ut.cpp
    integral_constant_ut.cpp
    is_pointer_ut.cpp
    is_reference_ut.cpp
    is_same_ut.cpp
    remove_reference_ut.cpp
)