cmake_minimum_required(VERSION 3.0.0)
project(api_server)

set(CMAKE_CXX_STANDARD 20)

option(TESTS "To build test?" ON)
option(STATIC_CHECKS "To use static checks?" OFF)
option(SANITIZE "To run TESTS with sanitize?" OFF)

if (TESTS)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
else()
  set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror -O0")
endif()

if(SANITIZE)
  string(APPEND CMAKE_C_FLAGS " -fsanitize=address,undefined,leak -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
  string(APPEND CMAKE_CXX_FLAGS " -fsanitize=address,undefined,leak -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
endif()

set(API_SERVER_LIBRARIES)
set(API_SERVER_INCLUDE_DIRS)
set(API_SERVER_SOURCES)


file(GLOB SOURCES router/src/*.cc
                  use_case/src/*.cc)
file(GLOB INCLUDE_DIRS  entities/inc
                        router/inc
                        use_case/inc)
# For clang-formate
file(GLOB INCLUDES  entities/inc/*.h
                    router/inc/*.h
                    use_case/inc/*.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

set(API_SERVER_LIBRARIES ${PROJECT_NAME})
set(API_SERVER_INCLUDE_DIRS ${INCLUDE_DIRS})
set(API_SERVER_SOURCES ${SOURCES})
set(API_SERVER_INCLUDES ${INCLUDES})

if (TESTS)
  add_subdirectory(tests)
endif()

if(STATIC_CHECKS)
  set(CMAKE_C_CLANG_TIDY 
    clang-tidy-12;
    -header-filter=.;
    -warnings-as-errors=*;
    -extra-arg=-std=c99;
    -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*)
endif()

add_custom_target(
        clang-format
        COMMAND clang-format-12
        -style=Chromium
        -n
        --Werror
        ${API_SERVER_SOURCES}
        ${API_SERVER_INCLUDES}
        ${TESTS_SOURCES}
        ${TESTS_INCLUDES}
)
