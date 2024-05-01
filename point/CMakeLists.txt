cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(point)

set(SRC
    sources/point.cpp
)

set(HEADERS
    headers/point.hpp
)

add_library(point
    ${SRC}
    ${HEADERS}
)
