cmake_minimum_required (VERSION 3.8)

project (SegmentIntersection)

include_directories(./segment/sources)
include_directories(./segment/headers)
include_directories(./point/sources)
include_directories(./point/headers)
include_directories(./service/sources)
include_directories(./service/headers)
include_directories(./headers)

set(POINT_S ./point/sources/Point.cpp)
set(POINT_H ./point/headers/Point.h)
add_library(point_lib ${POINT_S} ${POINT_H})

set(SEGMENT_S ./segment/sources/Segment.cpp)
set(SEGMNET_H ./segment/headers/Segment.h)
add_library(segment_lib ${SEGMENT_S} ${SEGMNET_H})

set(SERVICE_S ./service/sources/Service.cpp)
set(SERVICE_H ./service/headers/Service.h)
add_library(service_lib ${SERVICE_S} ${SERVICE_H})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} point_lib)
target_link_libraries(${PROJECT_NAME} segment_lib)
target_link_libraries(${PROJECT_NAME} service_lib)