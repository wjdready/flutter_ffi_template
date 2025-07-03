cmake_minimum_required(VERSION 3.10)

project(flutter_ffi_template VERSION 0.0.1 LANGUAGES C)

set(DART_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    "native/*.cpp"
    "${DART_SDK_PATH}/include/dart_api_dl.c"
)

include_directories(${DART_SDK_PATH})

add_library(flutter_ffi_template SHARED ${SOURCES})

if(WIN32)
    target_sources(flutter_ffi_template PRIVATE export.def)
endif()

