cmake_minimum_required(VERSION 3.9)
project(sp18_proj2_starter)

set(CMAKE_CXX_STANDARD 11)

add_executable(sp18_proj2_starter
        part1.c
        part2.c
        riscv.c
        riscv.h
        types.h
        utils.c
        utils.h)
