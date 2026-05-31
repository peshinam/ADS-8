cmake_minimum_required(VERSION 3.10)
project(WordFrequencyAnalysis)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/alg.cpp
)

add_executable(word_freq ${SOURCES})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/result)
