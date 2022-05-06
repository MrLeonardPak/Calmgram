cmake_minimum_required(VERSION 3.14.0)
project(tests)

set(TESTS_EXECUTABLE)
set(TESTS_INCLUDE_DIRS)
set(TESTS_SOURCES)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES src/*.cc)
file(GLOB INCLUDE_DIRS inc)
# For clang-formate
file(GLOB INCLUDS inc/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${API_SERVER_INCLUDE_DIRS} ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${API_SERVER_LIBRARIES} gtest_main gmock_main)

set(TESTS_EXECUTABLE ${PROJECT_NAME} PARENT_SCOPE)
set(TESTS_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
set(TESTS_SOURCES ${SOURCES} PARENT_SCOPE)
set(TESTS_INCLUDES ${INCLUDS} PARENT_SCOPE)


# Add valgrind to make target
add_custom_target(
        run_tests_with_valgrind
        COMMAND 
        valgrind
        --tool=memcheck
        --leak-check=full 
        --show-leak-kinds=all
        ${CMAKE_BINARY_DIR}/tests/${PROJECT_NAME} --gtest_filter=UserAuthUC.*:AddChatUC.*:SendMsgUC.*:UpdateChatUC.*
        # &&
        # valgrind
        # --tool=memcheck
        # --leak-check=full 
        # --show-leak-kinds=all
        # ${CMAKE_BINARY_DIR}/tests/${PROJECT_NAME} --gtest_filter=UserAuthHandler.* 
)

add_custom_target(
        run_tests
        COMMAND 
        ${CMAKE_BINARY_DIR}/tests/${PROJECT_NAME} --gtest_filter=UserAuthUC.*:AddChatUC.*:SendMsgUC.*:UpdateChatUC.*
        # &&
        # ${CMAKE_BINARY_DIR}/tests/${PROJECT_NAME} --gtest_filter=UserAuthHandler.* 
)