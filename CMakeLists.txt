cmake_minimum_required(VERSION 3.20)

project(minijs C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(minijs
    src/main.c
    src/utility.c
)

target_include_directories(minijs
    PRIVATE
        include
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

target_compile_options(minijs
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
)