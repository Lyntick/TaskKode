cmake_minimum_required(VERSION 3.30)
project(testTaskKode)

set(CMAKE_CXX_STANDARD 20)

add_executable(testTaskKode main.cpp
        Object.h
        ObjectManager.h
        ObjectManager.cpp)

