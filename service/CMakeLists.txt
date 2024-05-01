cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(service)

set(SRC
    sources/service.cpp
)

set(HEADERS
    headers/service.hpp
)

add_library(service
    ${SRC}
    ${HEADERS}
)

target_link_libraries(service PRIVATE
    point
    segment
)
