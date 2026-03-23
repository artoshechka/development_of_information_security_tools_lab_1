cmake_minimum_required(VERSION 3.16)
project(recursive_encoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(RECURSIVE_ENCODER_BUILD_TESTS "Build unit tests" OFF)

include(${CMAKE_SOURCE_DIR}/cmake/create_test.cmake)

if(RECURSIVE_ENCODER_BUILD_TESTS)
    include(CTest)
endif()

if(WIN32)
    set(CMAKE_PREFIX_PATH "")
    set(OPENSSL_ROOT_DIR "")
endif()


find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_subdirectory(recursive_stepper)
add_subdirectory(crypto_manager)
add_subdirectory(logger)

add_executable(${PROJECT_NAME}
  main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    crypto_manager
    recursive_stepper
  logger
    Qt${QT_VERSION_MAJOR}::Core
)

if(RECURSIVE_ENCODER_BUILD_TESTS)
  get_property(RECURSIVE_ENCODER_TEST_TARGETS GLOBAL PROPERTY RECURSIVE_ENCODER_TEST_TARGETS)
  if(RECURSIVE_ENCODER_TEST_TARGETS)
    add_custom_target(build_tests DEPENDS ${RECURSIVE_ENCODER_TEST_TARGETS})
  else()
    add_custom_target(build_tests)
  endif()
endif()