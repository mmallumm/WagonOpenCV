cmake_minimum_required(VERSION 3.0)
project(wagon_proj CXX)

set(SOURCES wagon.cpp)
set(HEADERS wagon.h)

find_package(OpenCV REQUIRED)

set(TARGET_NAME wagon_class)

add_library(${TARGET_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${TARGET_NAME} PUBLIC ${OpenCV_LIBS})

set(TARGET_NAME wagon_main)

add_executable(${TARGET_NAME} main.cpp)
target_link_libraries(${TARGET_NAME} PUBLIC wagon_class)
