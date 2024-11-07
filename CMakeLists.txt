cmake_minimum_required(VERSION 3.24)
project(BookStore)

set(CMAKE_CXX_STANDARD 17)

add_executable(BookStore main.cpp BookStore.cpp Book.cpp)
