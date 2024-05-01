cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(segment)

set(SRC
    sources/segment.cpp
)

set(HEADERS
    headers/segment.hpp
)

add_library(segment
    ${SRC}
    ${HEADERS}
)

target_link_libraries(segment PRIVATE
    point
    service
)
