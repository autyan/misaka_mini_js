cmake_minimum_required(VERSION 3.20)

project(minijs C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(minijs
    src/main.c
    src/app/app.c
    src/cli/cli.c
    src/runtime/runtime.c
    src/runtime/stream_file.c
    src/common/console.c
    src/common/log.c
    src/common/mj_error.c
    src/common/utility.c
)

if (WIN32)
    target_sources(minijs PRIVATE src/platform/platform_win.c)
else()
    target_sources(minijs PRIVATE src/platform/platform_posix.c)
endif()

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
