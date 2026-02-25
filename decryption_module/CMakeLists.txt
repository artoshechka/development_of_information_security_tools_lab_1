cmake_minimum_required(VERSION 3.2)
project(decryption_module LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
    src/decryption_module.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)