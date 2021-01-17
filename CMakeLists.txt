cmake_minimum_required(VERSION 3.16)
project(multiTypeTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(Source)

add_executable(multiTypeTree main.cpp source/multiTypeTree.h source/multiTypeTree.cpp source/tests/testTrees.h source/tests/testTrees.cpp source/tests/tests.cpp source/tests/tests.h)