cmake_minimum_required(VERSION 3.0.0)
project(api_server)
###############################################################################
set(CMAKE_CXX_STANDARD 20)
###############################################################################
# OPTIONS
option(TESTS "To build test" ON)
option(STATIC_CHECKS "To use static checks" OFF)
option(COVERAGE "Make coverage report" OFF)
option(SANITIZE "To run TESTS with sanitize" OFF)
option(MAIN_EXE "To run main code" OFF)
###############################################################################
# PREPARE
if (TESTS)
  set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -fPIC -O0 ")
else()
  set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} " -Wall -Wpedantic -Wextra -Werror -O0 ")
endif()
if (COVERAGE)
  string(APPEND CMAKE_EXE_LINKER_FLAGS " -coverage -lgcov ")
  string(APPEND CMAKE_CXX_FLAGS " -fprofile-arcs -ftest-coverage ")
endif()
if(SANITIZE)
  string(APPEND CMAKE_CXX_FLAGS " -fsanitize=address,undefined,leak -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
endif()
###############################################################################
# ADD POSTGRE SQL C++ LIB
# include(FetchContent)
# FetchContent_Declare(
#         libpqxx
#         GIT_REPOSITORY https://github.com/jtv/libpqxx.git
#         GIT_TAG 7.7.3
# )
# set(PQXX_LIBRARIES pqxx_static)
# FetchContent_MakeAvailable(libpqxx)
###############################################################################
# ADD LIBRARY
file(GLOB SOURCES use_case/src/*.cc
                  controller/src/*.cc
                  server/src/*.cc
                  libs/boost/server/src/*.cc)
file(GLOB INCLUDE_DIRS  entities/inc
                        use_case/inc
                        controller/inc    
                        server/inc
                        libs/boost/json
                        libs/boost/server/inc
                        /usr/local/include/boost_1_79_0)
# For clang-formate
file(GLOB INCLUDES  entities/inc/*.h
                    use_case/inc/*.h)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
###############################################################################
# SET VARIABLES
set(API_SERVER_LIBRARIES ${PROJECT_NAME})
set(API_SERVER_INCLUDE_DIRS ${INCLUDE_DIRS})
set(API_SERVER_SOURCES ${SOURCES})
set(API_SERVER_INCLUDES ${INCLUDES})
###############################################################################
# ADD EXECUTABLE FOR START SERVER
if (MAIN_EXE)
  add_executable(main_server main.cc)
  target_include_directories(main_server PUBLIC ${API_SERVER_INCLUDE_DIRS})
  target_link_libraries(main_server PRIVATE ${API_SERVER_LIBRARIES} pthread)
endif()
###############################################################################
# ADD TESTS
if (TESTS)
  add_subdirectory(tests)
endif()
###############################################################################
# ON STATIC CHECKS
if(STATIC_CHECKS)
  set(CMAKE_C_CLANG_TIDY 
    clang-tidy-12;
    -header-filter=.;
    -warnings-as-errors=*;
    -extra-arg=-std=c99;
    -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*)
endif()
###############################################################################
# ON CLANG FORMAT
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
###############################################################################