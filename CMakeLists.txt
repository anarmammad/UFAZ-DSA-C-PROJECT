cmake_minimum_required(VERSION 3.13)

project(UFAZ-DSA-C-Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(a.out main.c support/exception.c support/exception.h)
