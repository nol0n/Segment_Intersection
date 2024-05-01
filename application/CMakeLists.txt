cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(application)

add_executable(seg_test
    main.cpp
    test.hpp
)

target_include_directories(seg_test PRIVATE
    ./
)

target_link_libraries(seg_test PRIVATE
    point
    segment
    service
)
