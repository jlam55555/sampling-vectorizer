cmake_minimum_required(VERSION 3.14)
project(sampling_vectorizer)

set(CMAKE_CXX_STANDARD 14)

add_executable(sampling_vectorizer main.cpp)

find_package(PNG REQUIRED)
include_directories(/usr/include/png++ ${PNG_INCLUDE_DIR})

target_link_libraries(sampling_vectorizer ${PNG_LIBRARY})