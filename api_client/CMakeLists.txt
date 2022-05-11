cmake_minimum_required(VERSION 3.0.0)
project(api_client)

set(CMAKE_CXX_STANDARD 20)

option(TESTS "Do you want to build test?" OFF)

if (TESTS)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")
else()
    set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror -O0")
endif()

set(API_CLIENT_LIBRARIES)
set(API_CLIENT_INCLUDE_DIRS)
set(API_CLIENT_SOURCES)

file(GLOB SOURCES converters/src/*.cc
        network/src/*.cc
        use_case/src/*.cc
        user_interface/src/*.cpp
        user_interface/ui/*.ui
        core/src/*.cc)
#[[ add later user_interface/src/*.cc and user_interface/ui/*.ui]]

file(GLOB INCLUDE_DIRS  entities/inc
        converters/inc
        network/inc
        use_case/inc
        user_interface/inc
        core/inc
        /usr/local/include/boost_1_79_0)
#[[ add later user_interface/inc]]

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

set(API_CLIENT_LIBRARIES ${PROJECT_NAME})
set(API_CLIENT_INCLUDE_DIRS ${INCLUDE_DIRS})
set(API_CLIENT_SOURCES ${SOURCES})

add_executable(main_client main.cc)
target_include_directories(main_client PUBLIC ${API_CLIENT_INCLUDE_DIRS})
target_link_libraries(main_client PRIVATE ${API_CLIENT_LIBRARIES} pthread)

if (TESTS)
    add_subdirectory(tests)
endif()
