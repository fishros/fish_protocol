cmake_minimum_required(VERSION 3.8)
project(example_serial)

find_package(fish_protocol REQUIRED)

add_executable(example_serial example_serial.cpp)

target_link_libraries(example_serial fish_protocol)

