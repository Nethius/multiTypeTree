cmake_minimum_required(VERSION 3.16)
project(multiTypeTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(Source)

set(HEADERS
    source/multiTypeTree.h
    source/tests/testTrees.h
    source/tests/tests.h
)

set(SOURCES
    main.cpp
    source/multiTypeTree.cpp
    source/tests/testTrees.cpp
    source/tests/tests.cpp
)
add_executable(multiTypeTree ${SOURCES} ${HEADERS})