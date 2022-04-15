cmake_minimum_required(VERSION 3.0.0)
project(ml_model)

set(CMAKE_CXX_STANDARD 17)

option(TESTS "Do you want to build test?" OFF)
option(STATIC_CHECKS "Do you want to use static checks?" OFF)
option(SANITIZE "Do you want to run TESTS with sanitize?" OFF)

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


file(GLOB SOURCES Data/src/*.cc
                  NN/src/*.cc)
file(GLOB INCLUDE_DIRS  Data/inc
                        NN/inc)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

set(API_SERVER_LIBRARIES ${PROJECT_NAME})
set(API_SERVER_INCLUDE_DIRS ${INCLUDE_DIRS})
set(API_SERVER_SOURCES ${SOURCES})

if (TESTS)
  add_subdirectory(tests)
endif()

if(WITH_STATIC_CHECKS)
  set(CMAKE_C_CLANG_TIDY 
    clang-tidy-12;
    -header-filter=.;
    -warnings-as-errors=*;
    -extra-arg=-std=c99;
    -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*)
endif()

add_custom_target(
        clangformat
        COMMAND clang-format-12
        -style=Chromium
        -n
        --Werror
        ${API_SERVER_SOURCES}
        ${API_SERVER_INCLUDE_DIRS}/*.h
        ${TESTS_INCLUDE_DIRS}/*.cc
)

# Add valgrind to make target
add_custom_target(
        tests_with_valgrind
        COMMAND make
        -j8
        &&
        valgrind
        --tool=memcheck
        --leak-check=yes
        ${CMAKE_BINARY_DIR}/tests/${PROJECT_NAME}
)