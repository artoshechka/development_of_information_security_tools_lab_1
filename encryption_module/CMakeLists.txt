cmake_minimum_required(VERSION 3.2)
project(encryption_module LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
    src/encryption_module.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)