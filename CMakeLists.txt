cmake_minimum_required(VERSION 3.24.2)
project(IP_C_atalogue C)

set(CMAKE_C_STANDARD 99)

add_executable(IP_C_atalogue main.c
        headers/ipProcessing.h
        src/ipProcessing.c
)
