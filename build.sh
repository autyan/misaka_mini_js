#!/usr/bin/env bash

set -e

BUILD_TYPE="$1"

if [ "$BUILD_TYPE" = "debug" ]; then
    BUILD_DIR="build/debug"
    CMAKE_BUILD_TYPE="Debug"
elif [ "$BUILD_TYPE" = "release" ]; then
    BUILD_DIR="build/release"
    CMAKE_BUILD_TYPE="Release"
else
    echo "Usage: $0 [debug|release]"
    exit 1
fi

cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE"
cmake --build "$BUILD_DIR"
