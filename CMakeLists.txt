cmake_minimum_required(VERSION 3.2)
project(recursive_encoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_subdirectory(recursive_stepper)
add_subdirectory(decryption_module)
add_subdirectory(encryption_module)

add_executable(recursive_encoder
  main.cpp
)

target_link_libraries(recursive_encoder
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        recursive_stepper
        decryption_module
        encryption_module
)