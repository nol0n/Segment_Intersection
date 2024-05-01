cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  

project(SegmentIntersection)

include_directories(
    headers
    point/headers
    segment/headers
    service/headers
)

add_subdirectory(
    point
)

add_subdirectory(
    segment
)

add_subdirectory(
    service
)

add_subdirectory(
    application
)
