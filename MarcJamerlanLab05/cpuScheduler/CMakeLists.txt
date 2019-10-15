cmake_minimum_required(VERSION 3.8)

project(cpuScheduler)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-m64 -g -O0 -D_DEBUG -Wall")

set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES cpuScheduler.c processQueue.c)

add_executable(cpuScheduler ${SOURCE_FILES})
