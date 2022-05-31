cmake_minimum_required(VERSION 3.0.0)
project(api_client)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(API_CLIENT_LIBRARIES)
set(API_CLIENT_INCLUDE_DIRS)
set(API_CLIENT_SOURCES)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

find_package(Qt5Widgets REQUIRED)

file(GLOB SOURCES main.cc
    network/inc/*.h
    network/src/*.cc
    use_case/inc/*.h
    use_case/src/*.cc
    user_interface/inc/*.h
    user_interface/src/*.cc
    core/inc/*.h
    core/src/*.cc)

file(GLOB INCLUDE_DIRS  entities/inc
        network/inc
        use_case/inc
        user_interface/inc
        /usr/local/include/boost_1_79_0
        user_interface/inc
        core/inc)

set(API_CLIENT_INCLUDE_DIRS ${INCLUDE_DIRS})
set(API_CLIENT_SOURCES ${SOURCES})

add_executable(calmgram-client ${API_CLIENT_SOURCES})


target_include_directories(calmgram-client PUBLIC ${API_CLIENT_INCLUDE_DIRS} )
target_link_libraries(calmgram-client PRIVATE pthread Qt${QT_VERSION_MAJOR}::Widgets)
